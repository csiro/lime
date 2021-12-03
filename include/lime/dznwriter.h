#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

namespace lime {

    class DznWriter 
    {
    public:
        DznWriter(std::ostream& dzn) : dzn_(dzn) {}

        void write (const char* fldName, int val);
        void write (const char* fldName, double val);
        void write (const char* fldName, std::vector<int>& arrayOfInt);
        void write (const char* fldName, std::vector<double>& arrayOfFloat);
        void write (
            const char* fldName, std::vector<std::string>& arrayOfString,
            const bool quotes = true
        );
        void write (
            const char* fldName, std::vector<std::set<int>>& arrayOfSetOfInt
        );
        void write (
            const char* fldName,
            std::vector<std::vector<int>>& arrayOfArrayOfInt
        );
        /** Write the string in position k instead of integer k */
        void writeTranslated (
            const char* fldName, std::vector<int>& arrayOfInt,
            std::vector<std::string>,
            const bool quotes = true
        );
        void writeMetadata (std::string str);
        void comment (std::string str);
        
    private:
        void writeIntSet (std::set<int> theSet);
        
        std::ostream& dzn_;
    };

} //namespace

