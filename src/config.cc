#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

#include <lime/config.h>
#include <lime/strutil.h>
#include <lime/reader.h>
#include <lime/limetok.h>
#include <lime/error.h>
#include <lime/debug.h>

/** Give acccess to a config file */

using namespace lime;
using namespace std;

void
Config::setDefaults (vector<string> defaults)
{
    for (auto str : defaults) {
        addItem (str);
    }
}

void
Config::read (string filename)
{
    filename_ = filename;

    ifstream ifs (filename);
    if (!ifs.is_open())
        limeCrash (string("Can't open config file ") + filename);

    // Create a list of Config items (i.e. key/value pairs)
    int lineNum = 0;
    string line;
    while (std::getline(ifs, line)) {
        lineNum++;

        // Skip leading blanks
        auto keyStart = line.begin();
        while (keyStart != line.end()) {
            if (!isspace (*keyStart))
                break;
            keyStart++;
        }
        if (keyStart == line.end()) // Blank line
            continue;
        
        // Find first blank, '=' or ':'
        auto keyEnd = keyStart + 1;
        while (keyEnd != line.end()) {
            if (isspace (*keyEnd) || *keyEnd == ':' || *keyEnd == '=')
                break;
            keyEnd++;
        }
        
        // Find first non-blank
        auto valStart = keyEnd;
        if (valStart != line.end())
            valStart++;
        while (valStart != line.end()) {
            if (!isspace (*valStart))
                break;
            valStart++;
        }
        bool quotedString = false;
        if (valStart != line.end() && *valStart == '\"') {
            quotedString = true;
            valStart++;
        }
        if (valStart == line.end()) // Empty val
            limeCrash (
                "Bad format in config file at line " << lineNum <<
                " of " << filename
            );
            
        auto valEnd = valStart + 1;
        while (valEnd != line.end()) {
            if (quotedString) {
                // Look for close quote
                if (*valEnd == '\"')
                    break;
            }
            else if (isspace(*valEnd))
                break;
            valEnd++;
        }

        string key(keyStart, keyEnd);
        string val(valStart, valEnd);
        
        if (key[0] == '#') // Comment
            continue;

        if (val.length() == 0)
            limeCrash (
                "Bad format in config file at line " << lineNum <<
                " of " << filename
            );
        map_[toLower(key)] = val;
    }
}

void
Config::addItem (string key, string val)
{
    map_[toLower (key)] = val;
}

void
Config::addItem (const char* key, const char* val)
{
    addItem (string (key), string (val));
}

void
Config::addItem (string key, int val)
{
    map_[toLower (key)] = std::to_string(val);
}

void
Config::addItem (string key, long val)
{
    map_[toLower (key)] = std::to_string(val);
}

void
Config::addItem (string key, double val)
{
    map_[toLower (key)] = std::to_string(val);
}

void
Config::addItem (string key, unsigned long val)
{
    map_[toLower (key)] = std::to_string(val);
}

void
Config::addItem (string keyVal) 
{
    for (auto iter = keyVal.begin(); iter != keyVal.end(); ++iter) {
        if (*iter == ':' || *iter == '=') {
            // Found separator
            string key (keyVal.begin(), iter);
            string val (iter + 1, keyVal.end());
            addItem (key, val);
            break;
        }
    }
}


int
Config::getInt (string key, int defaultVal) 
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        // Remember default
        addItem (key, defaultVal);
        return defaultVal;
    }

    return stoi (strVal);
}
int
Config::getInt (const char* key, int defaultVal) 
{
    return getInt (string(key), defaultVal);
}

long
Config::getLong (string key, long defaultVal)
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        addItem (key, defaultVal);
        return defaultVal;
    }

    return stol (strVal);
}
long
Config::getLong (const char* key, long defaultVal)
{
    return getLong (string(key), defaultVal);
}

double
Config::getDouble (string key, double defaultVal)
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        addItem (key, defaultVal);
        return defaultVal;
    }

    return stod (strVal);
}
double
Config::getDouble (const char* key, double defaultVal)
{
    return getDouble (string(key), defaultVal);
}

unsigned long
Config::getUnsigned (string key, unsigned long defaultVal)
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        addItem (key, defaultVal);
        return defaultVal;
    }

    return stoul (strVal);
}
unsigned long
Config::getUnsigned (const char* key, unsigned long defaultVal)
{
    return getUnsigned (string(key), defaultVal);
}

bool
Config::getBool (string key, bool defaultVal)
{
    string strVal = toLower (valFor (key));
    if (strVal.length() == 0) { // Not there
        addItem (key, defaultVal);
        return defaultVal;
    }

    if (
        strVal.compare ("true") == 0 ||
        strVal.compare ("t") == 0 ||
        strVal.compare ("1") == 0
    )
        return true;
    
    return false;
}
bool
Config::getBool (const char* key, bool defaultVal)
{
    return getBool (string(key), defaultVal);
}

string
Config::getString (string key, string defaultVal)
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        addItem (key, defaultVal);
        return defaultVal;
    }
    
    return strVal;
}
string
Config::getString (const char* key, string defaultVal)
{
    return getString (string(key), defaultVal);
}

int
Config::getTime (string key, int defaultVal)
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        addItem (key, defaultVal);
        return defaultVal;
    }
    
    LimeTok ltok (strVal.c_str());
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
    
    return atol (hhStr) * 3600 + atol (mmStr) * 60 + atol (ssStr);
}

int
Config::getTime (const char* key, int defaultVal)
{
    return getTime (string(key), defaultVal);
}

string
Config::valFor(string key) const
{
    string uKey = toLower (key);
    auto iter = map_.find (uKey);
    if (iter == map_.end())
        return string("");
    return iter->second;
}

string
Config::show (const char* sep) const
{
    stringstream str;
    const char* currsep = "";
    for (auto iter = map_.begin(); iter != map_.end(); ++iter) {
        str << currsep << iter->first << " " << iter->second;
        currsep = sep;
    }
    return str.str();
}
