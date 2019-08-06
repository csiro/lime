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
        // Returns 1 if the first char is seen, 
        int expect (const char chr, const char chr2 = NO_CHAR);
        
        lime::Reader reader_;
        LimeTok ltok_;
        
        std::stringstream errorMsg_;
    };

} //namespace

