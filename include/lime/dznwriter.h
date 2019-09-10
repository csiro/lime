#pragma once

#include <iostream>
#include <vector>
#include <set>

namespace lime {

    class DznWriter 
    {
    public:
        DznWriter(const char* filename);
        DznWriter(std::string filename);

        void write (const char* fldName, int val);
        void write (const char* fldName, double val);
        void write (const char* fldName, std::vector<int>& arrayOfInt);
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
        
    private:
        void writeIntSet (std::set<int> theSet);
        
        std::ofstream dzn_;
    };

} //namespace

