
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <cassert>
#include <stdlib.h>

#include "lime/debug.h"
#include "lime/error.h"
#include "lime/strutil.h"
#include "lime/dznwriter.h"

using namespace std;
using namespace lime;

void
DznWriter::write (const char* fldName, int val)
{
    dzn_ << fldName << " = " << val << ";" << endl;
}
 
void
DznWriter::write (const char* fldName, double val)
{
    dzn_ << fldName << " = " << val << ";" << endl;
}

void
DznWriter::write (const char* fldName, std::vector<int>& arrayOfInt)
{
    dzn_ << fldName << " = [";
    if (arrayOfInt.size() > 0) {
        dzn_ << arrayOfInt[0];
        for (size_t i = 1; i < arrayOfInt.size(); i++)
            dzn_ << "," << arrayOfInt[i];
    }
    dzn_ << "];" << endl;
}

void
DznWriter::write (const char* fldName, std::vector<double>& arrayOfFloat)
{
    dzn_ << fldName << " = [";
    if (arrayOfFloat.size() > 0) {
        dzn_ << arrayOfFloat[0];
        for (size_t i = 1; i < arrayOfFloat.size(); i++)
            dzn_ << "," << arrayOfFloat[i];
    }
    dzn_ << "];" << endl;
}

void
DznWriter::writeTranslated (
    const char* fldName, std::vector<int>& arrayOfInt,
    std::vector<std::string> names,
    const bool quotes
)
{
    vector<string> strArray;
    for (int i : arrayOfInt) {
        if (i < 0 || i >= names.size()) 
            limeCrash (
                "Index " << i << " out of range while writing " <<
                fldName
            );
        strArray.push_back (names[i]);
    }
    write (fldName, strArray, quotes);
}

void
DznWriter::write (const char* fldName, vector<string>& arrayOfString, const bool quotes)
{
    dzn_ << fldName << " = [";
    if (arrayOfString.size() > 0) {
        if (quotes) {
            dzn_ << "\"" << arrayOfString[0] << "\"";
            for (size_t i = 1; i < arrayOfString.size(); i++)
                dzn_ << ", \"" << arrayOfString[i] << "\"";
        }
        else {
            dzn_ << arrayOfString[0];
            for (size_t i = 1; i < arrayOfString.size(); i++)
                dzn_ << "," << arrayOfString[i];
        }
    }
    dzn_ << "];" << endl;
}

void
DznWriter::write (
    const char* fldName, std::vector<std::set<int>>& arrayOfSetOfInt
)
{
    dzn_ << fldName << " = [";
    if (arrayOfSetOfInt.size() > 0) {
        writeIntSet (arrayOfSetOfInt[0]);
        for (size_t i = 1; i < arrayOfSetOfInt.size(); i++) {
            dzn_ << ",";
            writeIntSet (arrayOfSetOfInt[i]);
        }
    }
    dzn_ << "];" << endl;
}

void
DznWriter::write (
    const char* fldName, std::vector<std::vector<int>>& arrayOfArrayOfInt
)
{
    dzn_ << fldName << " = [|";
    const char* sep1 = "";
    for (size_t i = 0; i < arrayOfArrayOfInt.size(); i++) {
        dzn_ << sep1;
        const char* sep2 = "";
        for (size_t j = 0; j < arrayOfArrayOfInt[i].size(); j++) {
            dzn_ << sep2 << arrayOfArrayOfInt[i][j];
            sep2 = ",";
        }
        dzn_ << endl;
        sep1 = ",| ";
    }
    dzn_ << "|];" << endl;
}

void
DznWriter::writeMetadata (std::string str)
{
    dzn_ << "%%%meta-data: " << str << endl;
}

void
DznWriter::comment (std::string str)
{
    dzn_ << "% " << str << endl;
}

void
DznWriter::writeIntSet (std::set<int> theSet)
{
    dzn_ << "{";
    const char* sep = "";
    for (auto val : theSet) {
        dzn_ << sep << val;
        sep = ",";
    }
    dzn_ << "}";
}
