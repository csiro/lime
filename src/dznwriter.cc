#include <cassert>
#include <stdlib.h>

#include "lime/debug.h"
#include "lime/error.h"
#include "lime/strutil.h"
#include "lime/dznwriter.h"

using namespace std;
using namespace lime;

DznWriter::DznWriter (const char* filename) :
    dzn_()
{
    dzn_.open (filename, std::ofstream::out);
    if (!dzn_.good())
        limeCrash("Can't open DZN file for writing: " << filename);
}

DznWriter::DznWriter (string filename) :
    dzn_()
{
    dzn_.open (filename, std::ofstream::out);
    if (!dzn_.good())
        limeCrash("Can't open DZN file for writing: " << filename);
}

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
DznWriter::write (const char* fldName, vector<string>& arrayOfString)
{
    dzn_ << fldName << " = [";
    if (arrayOfString.size() > 0) {
        dzn_ << "\"" << arrayOfString[0] << "\"";
        for (size_t i = 1; i < arrayOfString.size(); i++)
            dzn_ << ",\"" << arrayOfString[i] << "\"";
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
