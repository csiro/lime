#pragma once

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
            const char* fldName, std::vector<std::string>& arrayOfString
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
            std::vector<std::string>
        );
        void comment (std::string str);
        
    private:
        void writeIntSet (std::set<int> theSet);
        
        std::ostream& dzn_;
    };

} //namespace

