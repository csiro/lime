#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
 * Tokenize a string safely - without the sttic storage used by strtok
 * Tokens are defined by delimiter in the string.
 * A default delimiter can be supplied at construction
 * If a double-quote is found, all delimiters are ignored until the
 * closing quote is found 
 */

#include <iostream>
#include <cassert>

class LimeTok
{
public:
    /** Empty tokeniser - use "tokenise" to initialise the string */
    LimeTok();
    /** Construct a tokeniser with the string to tokenise */
    LimeTok(const char* str);
    LimeTok(std::string str);
    virtual ~LimeTok();
    
    /** Reinitialsie with a new string to be tokenised.
        Invalidates "currToken"
    */
    void tokenise (const char* str);
    
    /** Return the next token
        Returns a pointer to the next token, or NULL if no more tokens
        Each call moves to the next token.
        If fromSet is non-null, then only advances with chars are in the set.
        If double-quote is seen, all delimiters are ignored until the
        closing double-quote is found
    */
    std::string nextToken(
        const char* delim = spaceOrTab(), bool skipLeadingSpaces = true,
        const char* fromSet = NULL
    );
    
    /** Return the token from the previous call to nextToken */
    std::string currToken() {
        return (curr_.length() == 0) ? std::string("") : curr_;
    }
    
    /** Return the next token as a string.
        Sets 'error' to true if there was a problem.
        Assumes space delimiters
    */
    std::string nextString(bool& error, const char* delim = spaceOrTab());
    /** Return the next token as an integer.
        Sets 'error' to true if there was a problem.
        Assumes space delimiters
    */
    int nextInt(bool& error, const char* delim = spaceOrTab());
    /** Return the next token as an double.
        Sets 'error' to true if there was a problem.
        Assumes space delimiters
    */
    double nextDouble(bool& error, const char* delim = spaceOrTab());
    /** Return the next token as an boolean.
        Legal bools are (ignoring case): 0, 1, t, f, true, false
        Sets 'error' to true if the token was not in this set.
        Assumes space delimiters
    */
    bool nextBool(bool& error, const char* delim = spaceOrTab());
    /** Return the next token as a time
        Assumes space delimiters.
        Assumes format is hh:mm:ss, or mm:ss, or sss
    */
    long nextTime (const char* delim = spaceOrTab());
        
    /** Return the next token as a C string.
        Assumes space delimiters
    */
    std::string nextString();
    /** Return the next token as an std::string.
        Assumes space delimiters
    */
    std::string nextStdString(bool& error);

    /** Return the next non-space char
    */
    char nextChar();
    
    /** Returns a space or tab - for use as a delimiter string */
    static const char* spaceOrTab() {return " 	";}

protected:
    // Move to the next char, stepping over escaped hars 
    char* nextChar (char* start);
    // Handle a " char
    char* handleQuote (char* start);

    size_t bufferLen_;
    char* buffer_;
    char* upto_;
    std::string curr_;
};


