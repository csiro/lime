/** Utility functions defined in error.h */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include "lime/debug.h"
#include "lime/error.h"


using namespace std;

LimeErrorImpl* LimeError::impl_ = NULL;

bool
LimeErrorImpl::tryOpenFile (string fn)
{
    bool ok = false;
    auto mode = ios_base::out;
    if (!truncate_)
        mode |= ios_base::app;
    try {
        logFile_.open (fn, mode);
        if (logFile_) {
            log_ = &logFile_;
            ok = true;
        }
    }
    catch (...) {
    }
    if (!ok) {
        cerr << "Could not open log file " << fn;
        log_ = &cerr;
    }
    return ok;
}

std::ostream&
LimeErrorImpl::log()
{
    if (!isOpen_) {
        if (fileName_.length() > 0) {
            isOpen_ = tryOpenFile(fileName_);
        }
        if (!isOpen_) {
            const char* limeDir = getenv ("LIME_LOG");
            if (limeDir == NULL)
                limeDir = ".";
            
            stringstream fn;
            fn << limeDir << "/crash.log";
            isOpen_ = tryOpenFile(fn.str());
        }
        // If still not open, use cerr as backup - set up in constructor
        // Treat as open
        isOpen_ = true;
    }
    return *log_;
}

std::string
LimeError::timeStr ()
{
    char buffer[1024];
    time_t theTime;
    time( &theTime );   // get the calendar time
    tm *t = localtime( &theTime );  // convert to local
    strftime (buffer, 1024, "%Y-%m-%d %H:%M:%S ", t);
    return std::string(buffer);
}

void
LimeError::warning ()
{
    cerr << "\rWarning:                                            " << endl;
    cerr << errorStream().str() << endl;
    log() << timeStr() << " Warning: " << errorStream().str() << endl;
    DEBUG ('a', "Warning: " << errorStream().str());
    errorStream().str("");
}

void
LimeError::crash ()
{
    cerr << "\rFatal error:                                            " << endl;
    cerr << errorStream().str() << endl;
    log() << timeStr() << " Fatal error: " << errorStream().str() << endl;
    DEBUG ('a', "Fatal: " << errorStream().str());
    errorStream().str("");
    exit(3);
}

void
LimeError::progress ()
{
    if (!getImpl()->quiet()) {
        cerr << "\r " << errorStream().str();
        cerr << "                                     \r" << flush;
        DEBUG ('a', "Progress " << errorStream().str());
        errorStream().str("");
    }
}

void
LimeError::_limeAssert (
    bool assertion, const char* file, int line
)
{
    if (!assertion) {
        limeCrash ("Assertion failed in " << file << " at line " << line); 
    }
}

