#ifndef LIME_DEBUG_H
#define LIME_DEBUG_H

#include <iostream>
#include <fstream>
#include <string>

#include "lime/scheduler.h"
#include "lime/strutil.h"

/** Using Debug

    Use debug via the following macros:

    DEBUG('x',Y)    If letter x is in the debug string (aka 'key'),
                    print using Y. Y can contain '<<' etc
    DEBUGT('x',Y)   Same as above, but current 'Scheduler' time is prepended
                    to the output string
    DEBUG_NL('x',Y) Same again, but no new line is appended
    DEBUG_ARR('x',M,A,N)  Print out an array. M is a message. A is the array,
                          accessed using 'A[i]'.  N is the size of the array.
                          Printed on one line
  
*/    

class Debug
{
public:
    Debug(const std::string& filename = "");
    virtual ~Debug() {};

    /** Set the debug keys to print to the debug file */
    static void setKey (const char * key);
    static void setFilename(const std::string& filename) {
        Debug::filename_ = filename;
    }
    static void setStartTime (int startTime);
    
    static bool doDebug (char);
    static std::ostream& debugFile();
    static int startTime() {return startTime_;}

private:
    static char key_[];
    static std::string filename_;
    static std::ofstream* outfile_;
    static int startTime_;
};

#ifdef NDEBUG

#define DEBUG(X,Y) {}
#define DEBUGT(X,Y) {}
#define DEBUG_NL(X,Y) {}
#define DEBUG_ARR(X,M,A,N) {}

#else

#define DEBUG(X,Y) {if (Debug::doDebug(X)){Debug::debugFile() << Y << std::endl; Debug::debugFile().flush();}}
#define DEBUGT(X,Y) {if (lime::Scheduler::currTime() >= Debug::startTime()) DEBUG(X,lime::fmtTime(lime::Scheduler::currTime()) << " " << Y);}
#define DEBUG_ARR(X,M,A,N) {if (Debug::doDebug(X)){Debug::debugFile()<<M;for(int idebug_=0;idebug_<N;idebug_++)Debug::debugFile() << A[idebug_] << " ";Debug::debugFile()<< endl; Debug::debugFile().flush();}}
#define DEBUG_NL(X,Y) {if (Debug::doDebug(X)){Debug::debugFile() << Y;}}

#endif // NDEBUG

#endif
