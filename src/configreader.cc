
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <iostream>
#include <algorithm>

#include <lime/configreader.h>
#include <lime/reader.h>
#include <lime/limetok.h>
#include <lime/error.h>

/** Read a config file */

using namespace lime;
using namespace std;

ConfigReader::ConfigReader (const char* filename) :
    filename_ (lime::strdup (filename)),
    items_(),
    used_(0)
{
    Reader reader (filename);

    // Create a list of Config items (i.e. key/value pairs)
    LimeTok ltok;
    char* line;
    int lineNum = 0;
    while ((line = reader.getLine()) != NULL) {
        lineNum++;
        ltok.tokenise (line);

        const char* key = ltok.nextString();
        const char* val = ltok.nextString();

        if (key == NULL)
            continue;
        if (*key == '#') // Comment
            continue;

        if (val == NULL)
            limeCrash (
                "Bad format in config file at line " << lineNum <<
                " of " << filename
            );
        items_.push_back (new ConfigItem (key, val));
    }
    used_ = new bool [items_.size()];
    std::fill (used_, used_ + items_.size(), false);
}

ConfigReader::ConfigReader (std::vector<const char*>& configs) :
    filename_ (lime::strdup ("args")),
    items_(),
    used_(0)
{
    // Create a list of Config items (i.e. key/value pairs)
    LimeTok ltok;
    int lineNum = 0;
    char keyBuffer[100];
    for (size_t i = 0; i < configs.size(); i++) {
        lineNum++;
        ltok.tokenise (configs[i]);
        const char* key = ltok.nextToken ("=:");
        if (key == NULL)
            continue;
        if (*key == '#') // Comment
            continue;
        strcpy (keyBuffer, key);
        if (
            configs[i][strlen(configs[i])-1] == ':' ||
            configs[i][strlen(configs[i])-1] == '='
        ) {
            // Value is on the next line
            ltok.tokenise (configs[++i]);
        }
        const char* val = ltok.nextToken (ltok.spaceOrTab());

        if (val == NULL)
            limeCrash (
                "Bad format in config file at line " << lineNum <<
                " of args, key is " << keyBuffer
            );
        items_.push_back (new ConfigItem (keyBuffer, val));
    }
    used_ = new bool [items_.size()];
    std::fill (used_, used_ + items_.size(), false);
}

ConfigReader::~ConfigReader () 
{
    if (filename_ != NULL)
        delete [] filename_;
    for (auto iter = items_.begin(); iter != items_.end(); ++iter) {
        delete *iter;
    }
    if (used_ != NULL)
        delete [] used_;
}

void
ConfigReader::readInt (const char* key, int& val) const
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;

    val = atoi (strVal);
}

void
ConfigReader::readLong (const char* key, long& val) const
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;

    val = atol (strVal);
}

void
ConfigReader::readDouble (const char* key, double& val) const
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;

    val = atof (strVal);
}

void
ConfigReader::readBool (const char* key, bool& val) const
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;

    if (
        lime::strcasecmp (strVal, "true") == 0 ||
        lime::strcasecmp (strVal, "t") == 0 ||
        lime::strcasecmp (strVal, "1") == 0
    )
        val = true;
    else 
        val = false;
}

void
ConfigReader::readString (const char* key, const char** val) const
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;

    (*val) = lime::strdup (strVal);
}

void
ConfigReader::readString (const char* key, string val)
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;

    val.assign (strVal);
}

void
ConfigReader::readTime (const char* key, int& val)
{
    long longVal = val;
    readTime (key, longVal);
    val = longVal;
}

void
ConfigReader::readTime (const char* key, long& val)
{
    const char* strVal = valFor (key);
    if (strVal == NULL) // Not there
        return;
    
    LimeTok ltok (strVal);
    const char* hhStr = ltok.nextToken (":");
    const char* mmStr = ltok.nextToken (":");
    const char* ssStr = ltok.nextToken (" ");

    if (mmStr == NULL) {
        // Only seconds - not in ":" format
        ssStr = hhStr;
        hhStr = "0";
        mmStr = "0";
    }
    if (ssStr == NULL) {
        // No seconds - assume 0
        ssStr = "0";
    }
    
    val = atol (hhStr) * 3600 + atol (mmStr) * 60 + atol (ssStr);
}

void
ConfigReader::close()
{
    assert (used_ != NULL);
    bool bad = false;
    for (size_t i = 0; i < items_.size(); i++) {
        if (!used_[i]) {
            bad = true;
            limeWarning ("Did not use config item " << items_[i]->key);
        }
    }
    if (bad)
        exit (1);
    
    delete [] used_;
    used_ = NULL;
}

const char*
ConfigReader::valFor(const char* key) const
{
    const char* val = NULL;
    for (size_t i = 0; i < items_.size(); i++) {
        if (lime::strcasecmp (key, items_[i]->key) == 0) {
            used_[i] = true;
            val = items_[i]->val;
            // Keep looking through, and pick up last val
        }
    }
    return val;
}
