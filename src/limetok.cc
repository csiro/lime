
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <16 May 2013 10:52:31>"

/** String tokeniser */

#include <ctype.h>
#include <assert.h>

#include "lime/limetok.h"
#include "lime/strutil.h"


LimeTok::LimeTok () :
    bufferLen_(0),
    buffer_(0),
    upto_(0),
    curr_(NULL)
{
}

LimeTok::LimeTok (const char* str) :
    bufferLen_(0),
    buffer_(0),
    upto_(0),
    curr_(NULL)
{
    tokenise (str);
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
        strcpy (buffer_, "");
        upto_ = buffer_;
        curr_ = NULL;
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
    curr_ = NULL;
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

char*
LimeTok::nextToken(const char* delim, bool skipLeadingDelim)
{
    if (strchr (delim, ' ') != 0)
        skipLeadingDelim = true;
    
    curr_ = NULL;
    if (upto_ == 0)
        return NULL;
    
    // Skip leading delimiters, if space is the delim
    if (skipLeadingDelim) {
        while (*upto_ != 0 && strchr (delim, *upto_) != NULL)
            upto_++;
    }
    if (*upto_ == 0)
        return NULL; // All done
    curr_ = upto_;
    while (*upto_ != 0 && strchr (delim, *upto_) == NULL) {
        if (*upto_ == '"') 
            upto_ = handleQuote (upto_);
        else
            upto_ = nextChar (upto_);
    }
    if (*upto_ != 0) {
        *upto_ = 0;
        upto_++; // Ready for next time
    }
    return curr_;
}


