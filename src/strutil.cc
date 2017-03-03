#include <cctype>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdio.h>

/** Lime string utilities */

#include "lime/strutil.h"

using namespace lime;
using namespace std;

char*
lime::strdup (const char* str)
{
    if (str == NULL)
        return NULL;
    char* copy = new char [strlen (str) + 1];
    return strcpy (copy, str);
}

char*
lime::trim (char* str)
{
    if (str == NULL)
        return NULL;

    char* c = str;
    while (*c != 0 && isspace(*c))
        c++;

    char* e = c + strlen (c) - 1;
    while (e > c && isspace(*e))
        e--;
    *(e + 1) = 0;
    return c;
}

int
lime::strcasecmp (const char* a, const char*b)
{
    if (a == NULL && b != NULL)
        return -1;
    if (a != NULL && b == NULL)
        return 1;
    if (a == NULL && b == NULL)
        return 0;
    
    while (*a > 0 || *b > 0) {
        int diff = tolower(*a) - tolower(*b);
        if (diff != 0)
            return diff;
        a++;
        b++;
    }
    return 0;
}

int
lime::strncasecmp (const char* a, const char*b, int n)
{
    if (a == NULL && b != NULL)
        return -1;
    if (a != NULL && b == NULL)
        return 1;
    if (a == NULL && b == NULL)
        return 0;

    for (int i = 0; i < n; i++) {
        int diff = tolower(*a) - tolower(*b);
        if (diff != 0)
            return diff;
        if (*a == 0) {
            if (*b == 0)
                return 0;
            return -1;
        }
        if (*b == 0)
            return 1;
        a++;
        b++;
    }
    return 0;
}

/** Return a formated time string */
char*
lime::todayStr (char* buffer, size_t bufferLen)
{
    time_t t;
    struct tm *tmp;
    
    t = time(NULL);
    tmp = localtime(&t);

    if (tmp == NULL)
        sprintf (buffer, "%*s", (int)bufferLen, "Error obtaining time");
    else 
        strftime (buffer, bufferLen, "%T %d/%m/%Y", tmp);
    return buffer;
}

/** Return a formated time string */
std::string
lime::todayString ()
{
    time_t t = time(NULL);
    struct tm *tim;
    tim = localtime(&t);

    if (tim == NULL)
        return string("Error obtaining time");

    std::ostringstream str;
    str <<
        setw(2) << setfill('0') << tim->tm_mday << "/" <<
        setw(2) << setfill('0') << tim->tm_mon << "/" <<
        setw(2) << setfill('0') << 1900 + tim->tm_year << " " << 
        setw(2) << setfill('0') << tim->tm_hour << ":" <<
        setw(2) << setfill('0') << tim->tm_min << ":" <<
        setw(2) << setfill('0') << tim->tm_sec;

    return str.str();
}

string
lime::toUpper (string str)
{
    for (char& c : str) {
        c = toupper (c);
    }
    return str;
}

string
lime::toLower (string str)
{
    for (char& c : str) {
        c = tolower (c);
    }
    return str;
}

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
char*
lime::extReplace (const char *filename, const char* ext, char* buffer)
{
    // Find last "/"
    const char* c = filename + strlen(filename) - 1;
    while (c > filename && *c != '/' && *c != '.')
        c--;

    if (*c == '/') // No "."
        c = filename + strlen(filename);

    // Copy up to c into buffer
    char* b = buffer;
    const char* a = filename;
    while (a < c)
        *(b++) = *(a++);

    // Append ext
    a = ext;
    while (*a)
        *(b++) = *(a++);
    *b = 0;

    return buffer;
}

/**  Strip directory AND extention off a file path
     E.g. lime::basename ("a/path/to/a/file.ext", buffer, 100)
     places "file" in buffer).
     Return value is buffer.
 */
char*
lime::basename (const char* path, char* buffer, size_t bufferLen)
{
    // Find last "/"
    const char* c = path + strlen(path);
    while (c > path && *(c - 1) != '/')
        c--;
    
    // Copy from c to '.' into buffer
    size_t count = 0;
    char* b = buffer;
    while (count++ < bufferLen && *c != 0 && *c != '.')
        *(b++) = *(c++);
    *b = 0;
    return buffer;
}

char*
lime::fmtTime (int secs, char* buffer)
{
    int hh = secs / (60 * 60); 
    secs -= hh * (60 * 60);
    int mm = secs / 60;
    secs -= mm * 60;
    sprintf (buffer, "%2.2d:%2.2d:%2.2d", hh, mm, secs);
    return buffer;
}
char*
lime::fmtDayTime (int secs, char* buffer)
{
    int days = secs / (60 * 60 * 24);
    secs -= days * (60 * 60 * 24);
    int hh = secs / (60 * 60); 
    secs -= hh * (60 * 60);
    int mm = secs / 60;
    secs -= mm * 60;
    sprintf (buffer, "%d %2.2d:%22.d:%2.2d", days, hh, mm, secs);
    return buffer;
}

char*
lime::fmtTime (int secs)
{
    static char buffer[20];
    return lime::fmtTime (secs, buffer);
}
char*
lime::fmtDayTime (int secs)
{
    static char buffer[20];
    return lime::fmtDayTime (secs, buffer);
}

char*
lime::itoa (int val)
{
    static char buffer[25];
    sprintf (buffer, "%d", val);
    return buffer;
}

std::string
lime::itostr (int val)
{
    char buffer[100];
    sprintf (buffer, "%d", val);
    return std::string(buffer);
}

std::string
lime::ltostr (long val)
{
    char buffer[100];
    sprintf (buffer, "%ld", val);
    return std::string(buffer);
}

std::string
lime::dtostr (double val)
{
    char buffer[100];
    sprintf (buffer, "%g", val);
    return std::string(buffer);
}
