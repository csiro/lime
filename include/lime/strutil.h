#pragma once

#include <string.h>
#include <string>

namespace lime {

/** Strdup (silly gygwin doesn't have it) */
    char* strdup (const char* str);
/** Trim leading and trailing spaces. Modifies string in-situ.
    Returns a pointer to first non-blank (or pointer to 0 if all blank
*/
    char* trim (char* str);
/** Trim leading spaces. */
    std::string ltrim (const std::string& str);
/** Trim trailing spaces. */
    std::string rtrim (const std::string& str);
/** Trim leading and trailing spaces. */
    std::string trim (const std::string& str);
/** stricmp */
    int strcasecmp (const char* a, const char*b);
/** strnicmp */
    int strncasecmp (const char* a, const char*b, int n);
/** Return current time as a formated time string */
    char* todayStr (char* buffer, size_t bufferLen);
/** Return current time as a formated time string */
    std::string todayString ();
/** Converts a string to upper case IN SITU. Returns the str argument */
    std::string toUpper (std::string str);
/** Converts a string to lower case IN SITU. Returns the str argument */
    std::string toLower (std::string str);
    
/** Converts a string to upper case IN SITU. Returns the str argument */
    char* toUpper (char* str);
/** Converts a string to lower case IN SITU. Returns the str argument */
    char* toLower (char* str);

/** Replace extension (if present) with given one.
    "Extension" is the what follows the last "." after
    the last "/" in filename (if present)
    Writes result in buffer.
    Buffer should be at least strlen(filename) + strlen(ext)
    Ext should include a "." if required
    Returns a pointer to buffer
    eg
    extReplace ("a/path/to/a.directory/filename.foo", ".bar", buffer);
    returns "a/path/to/a.directory/filename.bar" in buffer
    extReplace ("a/path/to/a.directory/filename", ".bar", buffer);
    returns "a/path/to/a.directory/filename.bar" in buffer
*/
    char* extReplace (const char *filename, const char* ext, char* buffer);
/**  Strip directory AND extention off a file path
     E.g. basename ("a/path/to/a/file.ext", buffer, 100)
     places "file" in buffer).
     Return value is buffer.
*/
    char* basename (const char*path, char* buffer, size_t bufferLen);

    /** Comparitor for Maps with char* keys */
    struct strCmp
    {
        bool operator() (const char* s1, const char* s2) const {
            return strcmp( s1, s2 ) < 0;
        }
    };
    /** Comparitor for Maps with string keys */
    struct stringCmp
    {
        bool operator() (std::string s1, std::string s2) const {
            return s1.compare(s2) < 0;
        }
    };
    

/** Format a time into "hh:mm:ss" */
    extern char* fmtTime (int secs, char* buffer);
/** Format a time into "days hh:mm:ss" */
    extern char* fmtDayTime (int secs, char* buffer);
/** As above, but use a static buffer */
    extern char* fmtTime (int secs);
    extern char* fmtDayTime (int secs);
/** String formatting */
    extern std::string fmtHhMm (int secs);

/** Return integer as char* */
    extern char* itoa (int val);
    extern std::string itostr (int val);
    extern std::string ltostr (long val);
    extern std::string dtostr (double val);

    extern const char pbdqWhirlygig (int k);
    extern const char whirlygig (int k);

    extern int kbhit(void);

} // namespace

