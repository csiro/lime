/** String splitter */

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <cassert>
#include <cctype>

#include "lime/splitter.h"
#include "lime/strutil.h"

using namespace std;
using namespace lime;

void
Splitter::split (string str, const char* delim, const char* commentChar)
{
    tokens_.clear();
    nextPos_ = 0;
    // No delims - the toke is the whole string
    if (strlen (delim) == 0) {
        tokens_.push_back (str);
        return;
    }

    if (str.length() + 1 > bufferLen_) {
        delete [] buffer_;
        bufferLen_ = str.length() + 1;
        buffer_ = new char [bufferLen_];
    }
        
    while (str.length() > 0) {
        //cout << "Str is >" << str << "<" << endl;
        if (delim[0] == ' ') {
            // Skip leading spaces
            size_t non_space = str.find_first_not_of (delim);
            if (non_space > 0)
                str.erase (0, non_space);
        }
        if (str.length() == 0)
            break;
        if (strchr (commentChar, str[0]) != NULL) {
            // Rest is comment
            break;
        }
        // Advance until we see a delim, and while we ae seeing
        // the right chars
        
        char* store = buffer_;
        bool inQuotes = false;
        size_t upto = 0;
        for (upto = 0; upto < str.length(); upto++) {
            //cout << "  Upto " << upto << " " << str[upto] << endl;
            if (!inQuotes && strchr (delim, str[upto]) != NULL) {
                // Found delim. Step over it
                upto++;
                break;
            }
            else if (!inQuotes && strchr (commentChar, str[upto]) != NULL) {
                // Found comment. 
                break;
            }
            if (str[upto] == '"') {
                inQuotes = !inQuotes;
            }
            else if (str[upto] == '\\') {
                // Copy next thing without looking
                upto++;
                if (upto < str.length())
                    *store++ = str[upto];
            }
            else {
                *store++ = str[upto];
            }
        }
        *store = 0;
        tokens_.push_back (buffer_);
        str.erase (0, upto);
    }
}

/** Return the next token as an integer.
    Sets 'error' to true if there was a problem.
    Assumes space delimiters
*/
int 
Splitter::nextInt(bool& error)
{
    string str = next(error);
    if (error)
        return 0;
    int val = 0;
    try {
        val = stoi (str);
    }
    catch (exception e) {
        error = true;
    }
    return val;
}

/** Return the next token as an double.
    Sets 'error' to true if there was a problem.
    Assumes space delimiters
*/
double 
Splitter::nextDouble(bool& error)
{
    string str = next(error);
    if (error)
        return 0;
    double val = 0;
    try {
        val = stod (str);
    }
    catch (exception e) {
        error = true;
    }
    return val;
}


/** Return the next token as an boolean.
    Legal bools are (ignoring case): 0, 1, t, f, true, false
    Sets 'error' to true if the token was not in this set.
    Assumes space delimiters
*/
bool
Splitter::nextBool(bool& error)
{
    string str = lime::toLower (next(error));
    if (error)
        return false;
    if (str.compare("0") == 0)
        return false;
    else if (str.compare ("1") == 0)
        return true;
    else if (str.compare ("f") == 0)
        return false;
    else if (str.compare ("t") == 0)
        return true;
    else if (str.compare ("y") == 0)
        return true;
    else if (str.compare ("n") == 0)
        return false;
    else if (str.compare ("false") == 0)
        return false;
    else if (str.compare ("true") == 0)
        return true;
    error = true;
    return false;
}

long
Splitter::nextTime (bool& error) 
{
    string str = next();
    Splitter split(str, ":");

    int hh = 0;
    int mm = 0;
    int ss = 0;

    if (split.numTokens() == 0) {
        error = true;
    }
    else if (split.numTokens() == 1) {
        // Treat it as mm
        mm = split.nextInt (error);
    }
    else if (split.numTokens() == 2) {
        // Treat it as hh:mm
        hh = split.nextInt (error);
        mm = split.nextInt (error);
    }
    else {
        // Treat it as hh:mm:ss
        hh = split.nextInt (error);
        mm = split.nextInt (error);
        ss = split.nextInt (error);
    }

    return (long) (hh * 3600 + mm * 60 + ss);
}
