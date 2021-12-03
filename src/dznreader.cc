
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <cassert>
#include <stdlib.h>

#include "lime/debug.h"
#include "lime/strutil.h"
#include "lime/dznreader.h"

using namespace std;
using namespace lime;

DznReader::DznReader (const char* filename) :
    reader_(filename),
    ltok_(),
    errorMsg_()
{
}

DznReader::DznReader (string filename) :
    reader_(filename),
    ltok_(),
    errorMsg_()
{
}

bool
DznReader::read (const char* fldName, int& val, bool failIfMissing)
{
    if (!find (fldName, failIfMissing))
        return false;
    bool error = false;
    val = ltok_.nextInt(error);
    return true;
}
 
bool
DznReader::read (const char* fldName, double& val, bool failIfMissing)
{
    if (!find (fldName, failIfMissing))
        return false;
    bool error = false;
    val = ltok_.nextDouble (error);
    return true;
}

bool
DznReader::read (
    const char* fldName, std::vector<int>& arrayOfInt, bool failIfMissing
)
{
    if (!find (fldName, failIfMissing))
        return false;
    expect ("[");
    bool error = false;
    int val = ltok_.nextInt(error);
    while (!error) { 
        arrayOfInt.push_back(val);
        if (expect (",]") != 1) // read the comma
            break;
        val = ltok_.nextInt(error);
    }
    return true;
}

bool
DznReader::readTranslated (
    const char* fldName, std::vector<int>& arrayOfInt,
    vector<string> names, bool failIfMissing
)
{
    arrayOfInt.clear();
    vector<string> strArr;
    if (!read (fldName, strArr, failIfMissing))
        return false;
    for (auto str : strArr) {
        string ustr = toUpper (str);
        bool found = false;
        for (unsigned i = 0; i < names.size(); i++) {
            if (ustr.compare (toUpper (names[i])) == 0) {
                arrayOfInt.push_back (i);
                found = true;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

bool
DznReader::read (
    const char* fldName, vector<string>& arrayOfString, bool failIfMissing
)
{
    if (!find (fldName, failIfMissing))
        return false;
    expect ("[");
    string str = ltok_.nextToken (",]", false);
    arrayOfString.push_back(str);
    while (expect (",]") == 1) { // While seeing commas
        str = ltok_.nextToken (",]");
        arrayOfString.push_back(str);
    }
    return true;
}

bool
DznReader::read (
    const char* fldName, std::vector<std::set<int>>& arrayOfSetOfInt,
    bool failIfMissing
)
{
    DEBUG ('D', "Read array of set of int " << fldName);
    if (!find (fldName, failIfMissing))
        return false;
    expect ("[");
    while (true) {
        std::set<int> theSet;
        if (expect ("{]") == 2) {
            // We've got the ']' - so we've finished the vector
            break;
        }
        bool error = false;
        int val = ltok_.nextInt(error);
        DEBUG ('D', "    First int " << val << " error " << error);
        if (!error) // error -> empty set - that's OK
            theSet.insert (val);
        while (expect (",}") == 1 && !error) { // While seeing commas
            val = ltok_.nextInt(error);
            DEBUG ('D', "    Next int " << val << " error " << error);
            theSet.insert (val);
        }
        arrayOfSetOfInt.push_back(theSet);
        DEBUG ('D', "  Finished set of size " << theSet.size());
        if (expect (",]") == 2) {
            // We've got the ']' - so we've finished the vector
            break;
        }
    }
    return true;
}

bool
DznReader::read (
    const char* fldName, std::vector<std::vector<int>>& arrayOfArrayOfInt,
    bool failIfMissing
)
{
    if (!find (fldName, failIfMissing))
        return false;
    expect ("[");
    while (true) {
        std::vector<int> theVector;
        if (expect ("|]") == 2) {
            // We've got the ']' - so we've finished the vector
            break;
        }
        DEBUG ('D', "Starting line " << arrayOfArrayOfInt.size());
        bool error = false;
        int val = ltok_.nextInt(error);
        DEBUG ('D', "  Val 0 is " << val << " error " << error);
        if (!error) // 'error' -> empty vector - that's OK
            theVector.push_back(val);
        // While seeing commas or EOL
        while (expect (",", true) == 1 && !error) { 
            val = ltok_.nextInt(error);
            DEBUG (
                'D', "  Val " << theVector.size() << " is " << val <<
                " error " << error
            );
            theVector.push_back (val);
        }
        arrayOfArrayOfInt.push_back(theVector);
        DEBUG ('D', "  vec size is now " << arrayOfArrayOfInt.size());
        // We need the next line
        char* line = reader_.getLine();
        if (line == NULL)
            readerError (&reader_, "EOF whole processing " << fldName);
        DEBUG ('D', "  line is " << line);
        ltok_.tokenise (line);
        if (expect (",|") == 2) {
            // we've finished the vector
            break;
        }
    }
    return true;
}

string
DznReader::readMetadata()
{
    bool found = false;
    reader_.rewind();
    char* line = 0;
    while (!found && (line = reader_.getLine()) != NULL) {
        if (strncmp (line, "%%%meta-data:", 13) == 0) {
            found = true;
            break;
        }
    }
    if (!found)
        return string("");
    char* c = line+13;
    while (*c != 0 && isspace(*c))
        c++;
    return string (c);
}


/* Find the line where the named field is defined.
   Eats the '='
   ltok_ contains the line.
 */
bool
DznReader::find (const char* fldName, bool failIfMissing)
{
    bool found = false;
    reader_.rewind();
    char* line = 0;
    while (!found && (line = reader_.getLine()) != NULL) {
        ltok_.tokenise (line);
        const char* tok = ltok_.nextString ();
        if (reader_.matches (tok, fldName)) 
            found = true;
    }
    if (!found) {
        if (failIfMissing) {
            readerError (&reader_, "Lost field name " << fldName);
        }
        else
            return false;
    }
    expect ("=");
    return true;
}

int
DznReader::expect (const char* chars, bool allowEOL)
{
    int pos = 1;
    char tok = ltok_.nextChar ();
    for (const char* c = chars; *c != 0; c++, pos++) {
        if (tok == *c) {
            DEBUG ('D', "      expect found " << *c);
            return pos;
        }
    }
    if (allowEOL && tok == 0)
        return strlen(chars) + 1;
    stringstream errStr;
    errStr << "Expected one of " << chars << " but got " << tok <<
        "(" << (int)tok << ")";
    readerError (&reader_, errStr.str());
    return 0;
}

