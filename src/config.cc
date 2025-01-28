
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/
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
#include <lime/fileutil.h>
#include <lime/debug.h>

/** Give acccess to a config file */

using namespace lime;
using namespace std;

Config::Config () :
    filename_ (std::string("(none)")),
    map_()
{
}

Config::Config (std::string filename) :
    filename_ (filename),
    map_()
{
    read (filename);
}

Config::Config (const Config& other) :
    filename_ (other.filename_),
    map_(other.map_)
{
}

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

    if (!lime::isFilename (filename))
        return;

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
        
        string key(keyStart, keyEnd);
        if (key[0] == '#') // Comment
            continue;

        // Find first non-blank
        auto valStart = keyEnd;
        if (valStart != line.end())
            valStart++;
        while (valStart != line.end()) {
            if (!isspace (*valStart))
                break;
            valStart++;
        }
        
        if (valStart == line.end()) // Empty val
            limeCrash (
                "Bad format in config file at line " << lineNum <<
                " of " << filename
            );
            
        auto valEnd = valStart + 1;
        auto upto = valEnd;
        while (upto != line.end() && *upto != '#') {
            if (!isspace(*upto))
                valEnd = upto+1;
            upto++;
        }

        string val(valStart, valEnd);
        
        if (val.length() == 0)
            limeCrash (
                "Bad format in config file at line " << lineNum <<
                " of " << filename
            );
        setVal (key, val);
    }
}

void
Config::addItem (string key, string val)
{
    setVal (key, val);
}

void
Config::addItem (const char* key, const char* val)
{
    addItem (string (key), string (val));
}

void
Config::addItem (string key, int val)
{
    setVal (key, std::to_string(val));
}

void
Config::addItem (string key, long val)
{
    setVal (key, std::to_string(val));
}

void
Config::addItem (string key, double val)
{
    stringstream str;
    str << val;
    setVal (key, str.str());
}

void
Config::addItem (string key, bool val)
{
    setVal (key, val ? "true" : "false");
}

void
Config::addItem (string key, unsigned long val)
{
    setVal (key, std::to_string(val));
}

void
Config::addItem (std::string key, std::vector<std::string> val)
{
    stringstream valStr;
    const char* sep = "";
    for (auto str : val) {
        valStr << sep << str;
        sep = " ";
    }
    addItem (key, valStr.str());
}

void
Config::addItem (std::string key, std::vector<int> val)
{
    stringstream valStr;
    for (auto i : val) {
        valStr << " " << std::to_string(i);
    }
    addItem (key, valStr.str());
}

void
Config::addItem (std::string key, std::vector<long> val)
{
    stringstream valStr;
    for (auto i : val) {
        valStr << " " << std::to_string(i);
    }
    addItem (key, valStr.str());
}

void
Config::addItem (std::string key, std::vector<unsigned long> val)
{
    stringstream valStr;
    for (auto i : val) {
        valStr << " " << std::to_string(i);
    }
    addItem (key, valStr.str());
}

void
Config::addItem (std::string key, std::vector<double> val)
{
    stringstream valStr;
    for (auto d : val) {
        valStr << " " << std::to_string(d);
    }
    addItem (key, valStr.str());
}

void
Config::addString(std::string key, std::string val)
{
    addItem (key, val);
}

void 
Config::addInt (std::string key, int val)
{
    addItem (key, val);
}

void 
Config::addLong (std::string key, long val)
{
    addItem (key, val);
}

void 
Config::addDouble (std::string key, double val)
{
    addItem (key, val);
}

void 
Config::addULong (std::string key, unsigned long val)
{
    addItem (key, val);
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
    int val = 0;
    try {
        val = stoi (strVal);
    }
    catch (std:: exception e) {
        // Ignore exceptions; use default
        val = defaultVal;
    }
    return val;
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

    long val = 0;
    try {
        val = stol (strVal);
    }
    catch (std:: exception e) {
        // Ignore exceptions; use default
        val = defaultVal;
    }
    return val;
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

    double val = 0;
    try {
        val = stod (strVal);
    }
    catch (std:: exception e) {
        // Ignore exceptions; use default
        val = defaultVal;
    }
    return val;
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
    
    unsigned long val = 0;
    try {
        val = stoul (strVal);
    }
    catch (std:: exception e) {
        // Ignore exceptions; use default
        val = defaultVal;
    }
    return val;
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
    string hhStr = ltok.nextToken (":");
    string mmStr = ltok.nextToken (":");
    string ssStr = ltok.nextToken ();
    if (mmStr == "") {
        // Only seconds - not in ":" format
        ssStr = hhStr;
        hhStr = "0";
        mmStr = "0";
    }
    if (ssStr == "") {
        // No seconds - assume 0
        ssStr = "0";
    }
    
    return stol (hhStr) * 3600 + stol (mmStr) * 60 + stol (ssStr);
}

int
Config::getTime (const char* key, int defaultVal)
{
    return getTime (string(key), defaultVal);
}

bool
Config::getVector (string key, vector<string>& vec)
{
    string strVal = valFor (key);
    if (strVal.length() == 0) { // Not there
        return false;
    }
    vec.clear();
    LimeTok tok (strVal);
    string str;
    while ((str = tok.nextToken(", ")) != "") {
        vec.push_back (str);
    }
    return true;
}

bool
Config::getVector (std::string key, std::vector<int>& vec)
{
    vector<string> strvec;
    if (!getVector (key, strvec))
        return false;
    vec.clear();
    for (auto str : strvec) {
        try {
            vec.push_back (stoi(str));
        }
        catch (std::exception e) {
            // Ignore;
        }
    }
    return true;
}

bool
Config::getVector (std::string key, std::vector<long>& vec)
{
    vector<string> strvec;
    if (!getVector (key, strvec))
        return false;
    vec.clear();
    for (auto str : strvec) {
        try {
            vec.push_back (stol(str));
        }
        catch (std::exception e) {
            // Ignore;
        }
    }
    return true;
}

bool
Config::getVector (std::string key, std::vector<unsigned long>& vec)
{
    vector<string> strvec;
    if (!getVector (key, strvec))
        return false;
    vec.clear();
    for (auto str : strvec) {
        try {
            vec.push_back (stoul(str));
        }
        catch (std::exception e) {
            // Ignore;
        }
    }
    return true;
}

bool
Config::getVector (std::string key, std::vector<double>& vec)
{
    vector<string> strvec;
    if (!getVector (key, strvec))
        return false;
    vec.clear();
    for (auto str : strvec) {
        try {
            vec.push_back (stod(str));
        }
        catch (std::exception e) {
            // Ignore;
        }
    }
    return true;
}

list<string>
Config::keys()
{
    list<string> keys;
    for (auto elt : map_)
        keys.push_back (elt.first);
    return keys;
}


void
Config::setVal (std::string key, std::string val)
{
    map_[toLower (key)] = val;
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
        str << currsep << iter->first << " ";
        if (iter->second.length() == 0) {
            // Write empty string
            str << "\"\"";
        }
        else if (iter->second.find(" ") != string::npos) {
            // there are spaces in the string.
            // Enclose in quotes
            str << "\"" << iter->second << "\"";
        }
        else
            str << iter->second;
        currsep = sep;
    }
    return str.str();
}
