#pragma once

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
        
        void read (const char* fldName, int& val);
        void read (const char* fldName, double& val);
        void read (const char* fldName, std::vector<int>& arrayOfInt);
        bool readTranslated (
            const char* fldName, std::vector<int>& arrayOfInt,
            std::vector<std::string> ids
        );
        void read (
            const char* fldName, std::vector<std::string>& arrayOfString
        );
        void read (
            const char* fldName, std::vector<std::set<int>>& arrayOfSetOfInt
        );
        void read (
            const char* fldName,
            std::vector<std::vector<int>>& arrayOfArrayOfInt
        );
        
    private:
        void find (const char* fldName);
        // Expect particular characters.
        // Returns 1-based pos of the char found, or 0 for not present
        int expect (const char* chars, bool allowEOL = false);
        
        lime::Reader reader_;
        LimeTok ltok_;
        
        std::stringstream errorMsg_;
    };

} //namespace

