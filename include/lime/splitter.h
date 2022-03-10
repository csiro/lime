#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
 * Split a string
 * Designed for either space-delimited, or comma-delimited strings.
 * Tokens are defined by delimiters in the string.
 * If the delim starts with a space
 * - Leading spaces are skipped
 * - Multiple spaces are skipped between tokens
 * All other delims are treated as singles, and can define 0-len tokens
 * A comment char can also be defined - everything after the comment
 *   char is ignored
 * If a double-quote is found, all delimiters are ignored until the
 * closing quote is found 
 */

#include <vector>
#include <string>

namespace lime {
    class Splitter
    {
    public:
        /** Empty splitter - use "split" to initialise the string */
        Splitter() :
            nextPos_(0),
            tokens_(),
            bufferLen_(1000),
            buffer_(new char[1000])
        {}
        /** Construct a tokeniser with the string to tokenise,
            the delimeters, and a comment char */
        Splitter(
            std::string str,
            const char* delim = spaceOrTab(),
            const char* commentChar = "#"
        ) :
            nextPos_(0),
            tokens_(),
            bufferLen_(1000),
            buffer_(new char[1000])
        {
            split (str, delim, commentChar);
        }
    
        virtual ~Splitter() {
            delete [] buffer_;
        }
    
        /** Reinitialsie with a new string to be split.
            When commentChar is seen, all other tokens are ignored
            Invalidates "currToken"
        */
        void split (
            std::string str,
            const char* delim = spaceOrTab(),
            const char* commentChar = "#"
        );
    
        /** Return the next token as a string, or a 0-length string
            if no more tokens are present.
            If the delim starts with a space
            - Leading spaces are skipped
            - Multiple spaces are skipped between tokens
            All other delims are treated as singles, and can define 0-len tokens
            (e.g. a CSV with ",,," defines 4 0-length strings);
            Each call moves to the next token.
            If double-quote is seen, all delimiters and comments are ignored
            until the closing double-quote is found
        */
        std::string next() {
            if (nextPos_ < (int)tokens_.size())
                return tokens_[nextPos_++];
            return std::string("");
        }
        /** Return the next token as a string.
            Set error to true if no more tokens */
        std::string next (bool& error) {
            if (nextPos_ < (int)tokens_.size())
                return tokens_[nextPos_++];
            error = true;
            return std::string("");
        }
        bool hasNext() const {return nextPos_ < tokens_.size();}
        std::string token(size_t k) const {
            return k < tokens_.size() ? tokens_[k] : std::string("");
        }
        size_t currPos() const {return (nextPos_ == 0) ? 0 : nextPos_ - 1;}
        size_t nextPos() const {return nextPos_;}
        size_t numTokens() const {return tokens_.size();}

        /** Return the rest of the tokens as a space-separated string */
        std::string rest() {
            std::string str("");
            std::string sep("");
            while (hasNext()) {
                str += sep + next();
                sep = " ";
            }
            return str;
        }
        
        /** Return the token from the previous call to nextToken */
        std::string currToken() const {return tokens_[currPos()];}

        /** Return the next token as a string.
            Sets 'error' to true if there was a problem.
            Just syntactic sugar for a 'next' call.
        */
        std::string nextString(bool& error) {return next(error);}
        
        /** Return the next token as an integer.
            Sets 'error' to true if there was a problem.
        */
        int nextInt(bool& error);
        /** Return the next token as an double.
            Sets 'error' to true if there was a problem.
            Assumes space delimiters
        */
        double nextDouble(bool& error);
        /** Return the next token as an boolean.
            Legal bools are (ignoring case): 0, 1, t, f, true, false
            Sets 'error' to true if the token was not in this set.
            Assumes space delimiters
        */
        bool nextBool(bool& error);
        /** Return the next token as a time
            Assumes space delimiters.
            Assumes format is hh:mm:ss, or mm:ss, or sss
        */
        long nextTime (bool& error);
        
        /** Returns a space or tab - for use as a delimiter string */
        static const char* spaceOrTab() {return " 	";}

        
        // Do the two strings match, up to the length of a
        static bool matches (std::string a, std::string b);
        // Do the two strings match ignoring case, up to the length of a
        static bool matchesIgnoreCase (std::string a, std::string b);
    
    private:

        size_t nextPos_;
        std::vector<std::string> tokens_;
        // For tokenising
        size_t bufferLen_;
        char *buffer_;
    };

} // namespace

