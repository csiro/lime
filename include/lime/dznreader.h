#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <sstream>
#include <vector>
#include <set>

#include "lime/reader.h"
#include "lime/limetok.h"

#define NO_CHAR (-1)

namespace lime {

    class DznReader 
    {
    public:
        DznReader(const char* filename);
        DznReader(std::string filename);

        std::string getErrorMsg () {return errorMsg_.str();}
        
        bool read (const char* fldName, int& val, bool failIfMissing = true);
        bool read (const char* fldName, double& val, bool failIfMissing = true);
        bool read (
            const char* fldName, std::vector<int>& arrayOfInt,
            bool failIfMissing = true
        );
        bool readTranslated (
            const char* fldName, std::vector<int>& arrayOfInt,
            std::vector<std::string> ids, bool failIfMissing = true
        );
        bool read (
            const char* fldName, std::vector<std::string>& arrayOfString,
            bool failIfMissing  = true
        );
        bool read (
            const char* fldName, std::vector<std::set<int>>& arrayOfSetOfInt,
            bool failIfMissing = true
        );
        bool read (
            const char* fldName,
            std::vector<std::vector<int>>& arrayOfArrayOfInt,
            bool failIfMissing = true
        );
        std::string readMetadata();
        
    private:
        bool find (const char* fldName, bool failIfMissing);
        // Expect particular characters.
        // Returns 1-based pos of the char found, or 0 for not present
        int expect (const char* chars, bool allowEOL = false);
        
        lime::Reader reader_;
        LimeTok ltok_;
        
        std::stringstream errorMsg_;
    };

} //namespace

