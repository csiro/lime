
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <cctype>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>

/** Lime string utilities */

#include "lime/strutil.h"
#include "lime/debug.h"

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


std::string
lime::ltrim(const std::string& s)
{
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string
lime::rtrim(const std::string& s)
{
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string
lime::trim(const std::string& s)
{
    return rtrim(ltrim(s));
}


int
lime::strcasecmp (const char* a, const char* b)
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

bool
lime::equal_ic (const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (sz != b.size())
        return false;
    
    for (unsigned int i = 0; i < sz; ++i) 
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    
    return true;
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
        setw(2) << setfill('0') << (tim->tm_mon + 1) << "/" <<
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

char*
lime::toUpper (char* str)
{
    for (char* c = str; *c != 0; c++) {
        *c = toupper (*c);
    }
    return str;
}

char*
lime::toLower (char* str)
{
    for (char* c = str; *c != 0; c++) {
        *c = tolower (*c);
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

string
lime::basename (string path)
{
    size_t len = path.length()+1;
    char* buffer = new char[len];
    char* base = basename (path.c_str(), buffer, len);
    return string(base);
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
    sprintf (buffer, "%3dd %2.2d:%2.2d:%2.2d", days, hh, mm, secs);
    return buffer;
}

char*
lime::fmtTime (int secs)
{
    static char buffer[100];
    return lime::fmtTime (secs, buffer);
}
char*
lime::fmtDayTime (int secs)
{
    static char buffer[100];
    return lime::fmtDayTime (secs, buffer);
}

string
lime::fmtHhMm (int secs)
{
    char buffer[100];
    int hh = secs / (60 * 60); 
    secs -= hh * (60 * 60);
    int mm = secs / 60;
    secs -= mm * 60;
    sprintf (buffer, "%2d:%2.2d", hh, mm);
    return string(buffer);
}

char*
lime::itoa (int val)
{
    static char buffer[100];
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

char
lime::whirlygig (int k)
{
    static const char* shape = "\\|/-";
    return shape[k % 4];
}
char
lime::pbdqWhirlygig (int k)
{
    static const char* shape = "pbdq";
    return shape[k % 4];
}

/**
 * Return the edit distance between two strings
 * Cost of add, del, mod and transpose is specified
 * Note: Could use less memeory, but I'm too lazy
 */
double lime::editDist (
    string a, string b,
    double addCost, double delCost, double modCost, double transCost
)
{
    int n = a.length() + 1;
    int m = b.length() + 1;
    vector<vector<double>> dist;
    for (size_t i = 0; i < n+1; i++)
        dist.push_back (vector<double>(m+1));
    
    dist[0][0] = 0;
    for (int i = 1; i < n; i++) 
        dist[i][0] = dist[i-1][0] + delCost;
    for (int j = 1; j < m; j++) 
        dist[0][j] = dist[0][j-1] + addCost;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            // Assume modify
            double best = dist[i-1][j-1] + modCost;
                
            if (a[i-1] == b[j-1])
                best = dist[i-1][j-1]; // Copy (no cost)
            if (dist[i-1][j] + delCost < best)
                best = dist[i-1][j] + delCost;
            if (dist[i][j-1] + addCost < best)
                best = dist[i][j-1] + addCost; 
            if (
                i > 1 && j > 1 &&
                a[i-1] == b[j-2] &&
                a[i-2] == b[j-1] &&
                dist[i-2][j-2] + transCost < best
            )
                best = dist[i-2][j-2] + transCost;
                
            dist[i][j] = best;
        }
    }

    if (false) {
        DEBUG_NL ('e', "  ");
        for (int j = 1; j < m; j++) 
            DEBUG_NL ('e', "  " << b[j-1]);
        DEBUG ('e', "");
        for (int i = 0; i < n; i++) {
            DEBUG_NL ('e', ((i > 0) ? a[i-1] : ' '));
            for (int j = 0; j < m; j++) 
                DEBUG_NL('e', " " << setw(4) << dist[i][j]);
            DEBUG('e',"");
        }
    }
    return dist[n-1][m-1];
}

string lime::escSeq (EscSeqAction action, int row, int col)
{
    switch (action) {
    case CLRSCR_HOME:
        return "\e[2J\e[1;0H";
    case POS:
        return "\e[" + to_string(row) + ";" + to_string(col) + "H";
    case CLR_LINE:
        return "\e[K";
    case UP:
        return "\e[" + to_string(row) + "A";
    case DOWN:
        return "\e[" + to_string(row) + "B";
    case LEFT:
        if (col == 0)
            col = row;
        return "\e[" + to_string(col) + "D";
    case RIGHT:
        if (col == 0)
            col = row;
        return "\e[" + to_string(col) + "C";
    }
    return "";
}

/** Test if keyboard has been hit */

#ifdef _MSC_VER
// This doesn't work on visual c++
int
lime::kbhit(void)
{
    return 0;
}

#else

#include <sys/select.h>
int
lime::kbhit(void)
{
    struct timeval tv;
    fd_set read_fd = {}; // Avoid scan-build false positive report for FD_SET
    
    tv.tv_sec=0;
    tv.tv_usec=0;
    FD_ZERO(&read_fd);
    FD_SET(0,&read_fd);
    
    if(select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;
    
    if(FD_ISSET(0,&read_fd))
        return 1;
    
    return 0;
}
#endif
