/** Utility functions defined in error.h */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include "lime/debug.h"
#include "lime/error.h"


bool limeQuiet = false;
std::stringstream _limeErrorLine;

using namespace std;

void
_limeLog (std::stringstream& str)
{
    const char* limeDir = getenv ("LIME_LOG");
    if (limeDir == NULL)
        limeDir = ".";

    char buffer[1024];
    sprintf (buffer, "%s/crash.log", limeDir);
    
    ofstream log (buffer, ios_base::out | ios_base::app);
    if (log) {
        time_t theTime;
        time( &theTime );   // get the calendar time
        tm *t = localtime( &theTime );  // convert to local
        strftime (buffer, 1024, "%Y-%m-%d %H:%M:%S ", t);
        log << buffer << str.str() << endl;
        log.close();
        str.str("");
    }
    else
        cerr << "Couldn't open log file " << buffer << endl;
}

void
_limeProgress (std::stringstream& str)
{
    if (!limeQuiet) {
        cerr << "\r " << str.str();
        cerr << "                   \r" << flush;
        DEBUG ('a', "Progress " << str.str());
    }
}

void
_limeCrash (std::stringstream& str)
{
    cerr << "\rFatal error:                                        " << endl;
    cerr << str.str() << endl;
    std::stringstream logStream;
    logStream << "Fatal error: " << str.str();
    limeLog (logStream);
#ifndef NDEBUG
    Debug::debugFile().flush ();
#endif
    assert(0);
    exit (3);
}

void
_limeWarning (std::stringstream& str)
{
    cerr << "\rWarning:                                            " << endl;
    cerr << str.str() << endl;
    std::stringstream logStream;
    logStream << "Warning:" << str.str();
    limeLog (logStream);
    DEBUG ('a', "Warning: " << str.str());
    str.str("");
}

void _limeAssert (
    bool assertion, const char* file, int line
)
{
    if (!assertion) {
        limeCrash ("Assertion failed in " << file << " at line " << line); 
    }
}

