/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

/** String tokeniser */

#include <ctype.h>
#include <stdlib.h>
#include <cassert>
#include <cctype>

#include "lime/limetok.h"
#include "lime/debug.h"
#include "lime/strutil.h"

LimeTok::LimeTok () :
    bufferLen_(0),
    buffer_(0),
    upto_(0),
    curr_()
{
}

LimeTok::LimeTok (const char* str) :
    bufferLen_(0),
    buffer_(0),
    upto_(0),
    curr_()
{
    tokenise (str);
}

LimeTok::LimeTok (std::string str) :
    bufferLen_(0),
    buffer_(0),
    upto_(0),
    curr_()
{
    tokenise (str.c_str());
}

LimeTok::~LimeTok ()
{
    if (buffer_ != NULL)
        delete [] buffer_;
}

void
LimeTok::tokenise (const char* str)
{
    if (str == NULL) {
        if (buffer_ != NULL) 
            strcpy (buffer_, "");
        upto_ = buffer_;
        curr_ = std::string("");
        return;
    }
    size_t len = strlen (str) + 1;
    // If I can, just re-use my existing memory
    // Otherwise, allocate a bigger chunk
    if (len > bufferLen_) {
        if (buffer_ != NULL)
            delete [] buffer_;
        buffer_ = new char [len];
        bufferLen_ = len;
    }
    strcpy (buffer_, str);
    upto_ = buffer_;
    curr_ = std::string("");
}

char*
LimeTok::nextChar (char* start)
{
    start++;
    // If the next char is an escape, we need to skip whatever is next
    if (*start == '\\') {
        start++;
        if (*start != 0)
            start++;
    }
    return start;
}


char*
LimeTok::handleQuote (char* start)
{
    assert (*start == '"');
    char* from = start + 1;
    char* to = start; 
    // Whe we see a quote, copy everything, we have to
    // overwrite it, copying down everything until the next quote
    while (*from != 0 && *from != '"') { 
        *(to++) = *(from++);
        if (strncmp (from, "\\\"", 2) == 0) {
            // copy the escaped quote (without escape)
            from++;
            *(to++) = *(from++);
        }
    }
    if (*from != 0)
        from++;
    char* next = to;
    while (*from != 0)
        *(to++) = *(from++);
    // Terminate the string
    *to = 0;
    return next;
}

std::string
LimeTok::nextToken(
    const char* delim, bool skipLeadingSpaces, const char* fromSet
)
{
    //DEBUG ('D', "nexttoken at upto >" << upto_ << "<");
    curr_ = std::string("");
    if (upto_ == 0)
        return "";
    
    if (skipLeadingSpaces) {
        //DEBUG ('D', "  skipleading");
        while (*upto_ != 0 && strchr (spaceOrTab(), *upto_) != NULL)
            upto_++;
    }
    //DEBUG ('D', "  upto now >" << upto_ << "<");
    if (*upto_ == 0)
        return ""; // All done
    const char* start = upto_;
    // Advance until we see a delim, and while we ae seeing
    // the right chars
    while (
        *upto_ != 0 &&
        strchr (delim, *upto_) == NULL &&
        (fromSet == NULL || (strchr (fromSet, *upto_) != 0))
    ) {
        if (*upto_ == '"') 
            upto_ = handleQuote (upto_);
        else 
            upto_ = nextChar (upto_);
    }
    // Temporarily 0-terminate so we can grab string
    char tmp = *upto_;
    *upto_ = 0;
    curr_.assign (start);
    *upto_ = tmp;
    //DEBUG ('D', "  found >" << curr_ << "<");
    //DEBUG ('D', "  upto now >" << upto_ << "<");
    if (*upto_ != 0 && strchr (delim, *upto_) != NULL) {
        // We stopped at a delim, so step over it
        upto_++;
        //DEBUG ('D', "  step to >" << upto_ << "<");
    }

    return curr_;
}
/** Return the next token as a string.
    Sets 'error' to true if there was a problem.
*/
std::string
LimeTok::nextString(bool& error, const char* delim)
{
    std::string tok = nextToken (delim, true);
    if (tok == "") 
        error = true;
    return tok;
}

/** Return the next token as an integer.
    Sets 'error' to true if there was a problem.
*/
int 
LimeTok::nextInt(bool& error, const char* delim)
{
    const char* from = "0123456789+-";
    std::string tok = nextToken (delim, true, from);
    if (tok == "" || strchr (from, tok[0]) == NULL) {
        error = true;
        return 0;
    }
    return std::stoi (tok);
}

/** Return the next token as an double.
    Sets 'error' to true if there was a problem.
*/
double 
LimeTok::nextDouble(bool& error, const char* delim)
{
    const char* from = "0123456789+-e.";
           
    std::string tok = nextToken (delim, true, from);
    if (tok == "" || (strchr (from, tok[0]) == NULL)) {
        error = true;
        return 0.0;
    }
    return std::stod (tok);
}


/** Return the next token as an boolean.
    Legal bools are (ignoring case): 0, 1, t, f, true, false
    Sets 'error' to true if the token was not in this set.
*/
bool
LimeTok::nextBool(bool& error, const char* delim)
{
    std::string tok = nextToken (delim, true, "01truefalsTRUEFALS");
    if (tok != "") {
        if (tok == "0")
            return false;
        else if (tok == "1")
            return true;
        else if (tok == "f" || tok == "F")
            return false;
        else if (tok == "t" || tok == "T")
            return true;
        else if (lime::strcasecmp (tok.c_str(), "false") == 0)
            return false;
        else if (lime::strcasecmp (tok.c_str(), "true") == 0)
            return true;
    }
    error = true;
    return false;
}

long
LimeTok::nextTime (const char* delim) 
{
    std::string tok = nextToken (delim, true, "0123456789:.");
    if (tok == "")
        return 0;
    LimeTok ltok2 (tok);

    std::string hhStr = ltok2.nextToken (":");
    std::string mmStr = ltok2.nextToken (":");
    std::string ssStr = ltok2.nextToken (":");
    int hh = 0;
    int mm = 0;
    int ss = 0;
    if (hhStr == "")
        return 0;
    if (ssStr == "" || mmStr == "") {
        // It is a seconds-only time
        ss = std::stoi (hhStr);
    }
    else {
        hh = std::stoi (hhStr);
        mm = std::stoi (mmStr);
        ss = std::stoi (ssStr);
    }
    return hh * 3600 + mm * 60 + ss;
}

/** Return the next token as a C string.
    Assumes space delimiters
*/
std::string
LimeTok::nextString()
{
    return nextToken (spaceOrTab(), true);
}

/** Return the next token as an std::string.
    Assumes space delimiters
*/
std::string
LimeTok::nextStdString(bool& error)
{
    std::string tok = nextToken (spaceOrTab(), true);
    if (tok == "") {
        error = true;
    }
    return std::string(tok);
}

char
LimeTok::nextChar()
{
    if (upto_ == 0)
        return 0;
    
    // Skip leading spaces
    while (*upto_ != 0 && isspace (*upto_))
        upto_++;
    
    if (*upto_ == 0)
        return 0; // All done
    // Step upto ready for next call
    curr_ = upto_;
    return *upto_++;
}


