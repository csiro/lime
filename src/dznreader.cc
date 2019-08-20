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

void
DznReader::read (const char* fldName, int& val)
{
    find (fldName);
    bool error = false;
    val = ltok_.nextInt(error);
}
 
void
DznReader::read (const char* fldName, double& val)
{
    find (fldName);
    bool error = false;
    val = ltok_.nextDouble (error);
}

void
DznReader::read (const char* fldName, std::vector<int>& arrayOfInt)
{
    find (fldName);
    expect ('[');
    bool error = false;
    int val = ltok_.nextInt(error);
    arrayOfInt.push_back(val);
    while (expect (',', ']') == 1 && !error) { // While seeing commas
        val = ltok_.nextInt(error);
        arrayOfInt.push_back(val);
    }
}

void
DznReader::read (const char* fldName, vector<string>& arrayOfString)
{
    find (fldName);
    expect ('[');
    string str = ltok_.nextToken (",]", false);
    arrayOfString.push_back(str);
    while (expect (',', ']') == 1) { // While seeing commas
        str = ltok_.nextToken (",]", false);
        // Need to remove spaces ...
        arrayOfString.push_back(str);
    }
}

void
DznReader::read (
    const char* fldName, std::vector<std::set<int>>& arrayOfSetOfInt
)
{
    DEBUG ('D', "Read array of set of int " << fldName);
    find (fldName);
    expect ('[');
    while (true) {
        std::set<int> theSet;
        if (expect ('{', ']') == 2) {
            // We've got the ']' - so we've finished the vector
            break;
        }
        bool error = false;
        int val = ltok_.nextInt(error);
        DEBUG ('D', "    First int " << val << " error " << error);
        if (!error) // error -> empty set - that's OK
            theSet.insert (val);
        while (expect (',', '}') == 1 && !error) { // While seeing commas
            val = ltok_.nextInt(error);
            DEBUG ('D', "    Next int " << val << " error " << error);
            theSet.insert (val);
        }
        arrayOfSetOfInt.push_back(theSet);
        DEBUG ('D', "  Finished set of size " << theSet.size());
        if (expect (',', ']') == 2) {
            // We've got the ']' - so we've finished the vector
            break;
        }
    }
}

void
DznReader::read (
    const char* fldName, std::vector<std::vector<int>>& arrayOfArrayOfInt
)
{
    find (fldName);
    expect ('[');
    while (true) {
        std::vector<int> theVector;
        if (expect ('|', ']') == 2) {
            // We've got the ']' - so we've finished the vector
            break;
        }
        DEBUG ('D', "Starting line " << arrayOfArrayOfInt.size());
        bool error = false;
        int val = ltok_.nextInt(error);
        DEBUG ('D', "  Val 0 is " << val << " error " << error);
        if (!error) // 'error' -> empty vector - that's OK
            theVector.push_back(val);
        while (expect (',', 0) == 1 && !error) { // While seeing commas
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
        if (expect (',', '|') == 2) {
            // we've finished the vector
            break;
        }
    }
}

/* Find the line where the named field is defined.
   Eats the '='
   ltok_ contains the line.
 */
void
DznReader::find (const char* fldName)
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
    if (!found)
        readerError (&reader_, "Lost field name " << fldName);
    expect ('=');
}

int
DznReader::expect (const char chr, const char chr2)
{
    char tok = ltok_.nextChar ();
    if (tok == chr) {
        DEBUG ('D', "      expect found " << chr);
        return 1;
    }
    if (chr2 != NO_CHAR && tok == chr2) {
        DEBUG ('D', "      expect found " << chr2);
        return 2;
    }
    stringstream errStr;
    errStr << "Expected " << chr;
    if (chr2 != 0)
        errStr << " or " << chr2;
    errStr << " but got " << tok << "(" << (int)tok << ")";
    readerError (&reader_, errStr.str());
    return 0;
}

