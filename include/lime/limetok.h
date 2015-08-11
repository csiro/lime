#ifndef LIME_TOK_H
#define LIME_TOK_H

/**
 * Tokenize a string safely - without the sttic storage used by strtok
 * Tokens are defined by delimiter in the string.
 * A default delimiter can be supplied at construction
 * If a double-quote is found, all delimiters are ignored until the
 * closing quote is found 
 */

#include <iostream>
#include <assert.h>

class LimeTok
{
public:
    /** Empty tokeniser - use "tokenise" to initialise the string */
    LimeTok();
    /** Construct a tokeniser with the string to tokenise */
    LimeTok(const char* str);
    virtual ~LimeTok();
    
    /** Reinitialsie with a new string to be tokenised.
        Invalidates "currToken"
    */
    void tokenise (const char* str);
    
    /** Return the next token
        Returns a pointer to the next token, or NULL if no more tokens
        Each call moves to the next token. 
        If space is a valid separator, skips leading spaces.
        The returned string can be modified without affecting the original
        string, or the results of the next call to nextToken
        If double-quote is seen, all delimiters are ignored until the
        closing double-quote is found
    */
    char* nextToken(const char* delim, bool skipLeadingDelim = false);
    /** Return the token from the previous call to nextToken */
    char* currToken() {return curr_;};

    /** Returns a space or tab - for use as a delimiter string */
    const char* spaceOrTab() const {return " 	";}

protected:
    // Move to the next char, stepping over escaped hars 
    char* nextChar (char* start);
    // Handle a " char
    char* handleQuote (char* start);

    size_t bufferLen_;
    char* buffer_;
    char* upto_;
    char* curr_;
};


#endif
