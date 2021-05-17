#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

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
    static void setKey (std::string key) {setKey (key.c_str());}
    static void setFilename(const std::string& filename) {
        Debug::filename_ = filename;
    }
    static void setStartTime (int startTime);

    static const char* keys() {return key_;}
    static bool doDebug (char);
    static std::ostream& debugFile();
    static int startTime() {return startTime_;}

private:
    static char key_[];
    static std::string filename_;
    static std::ofstream* outfile_;
    static int startTime_;
};

// Keep the compiler happy about unused vars
#define USE(X) {(void)X;}

namespace lime {
    std::string buildId (std::string dateStr, std::string timeStr);
}

#ifdef NDEBUG

#define DEBUG(X,Y) {}
#define DEBUGT(X,Y) {}
#define DEBUG_NL(X,Y) {}
#define DEBUG_ARR(X,M,A,N) {}
#define DEBUG_VEC(X,M,A) {}
#define DEBUG_PTRVEC(X,M,A) {}

#else

#define DEBUG(X,Y) {if (Debug::doDebug(X)){Debug::debugFile() << Y << std::endl; Debug::debugFile().flush();}}
#define DEBUGT(X,Y) {if (lime::Scheduler::currTime() >= Debug::startTime()) DEBUG(X,lime::fmtDayTime(lime::Scheduler::currTime()) << " " << Y);}
#define DEBUG_ARR(X,M,A,N) {if (Debug::doDebug(X)){Debug::debugFile()<<M;for(auto idebug_=0;idebug_<N;idebug_++)Debug::debugFile() << A[idebug_] << " ";Debug::debugFile()<< endl; Debug::debugFile().flush();}}
#define DEBUG_VEC(X,M,A) {if (Debug::doDebug(X)){Debug::debugFile()<<M;for(size_t idebug_=0;idebug_<A.size();idebug_++)Debug::debugFile() << A[idebug_] << " ";Debug::debugFile()<< endl; Debug::debugFile().flush();}}
#define DEBUG_IVEC(X,M,A) {if (Debug::doDebug(X)){Debug::debugFile()<<M;for(auto debug_iter=A.begin();debug_iter!=A.end();++debug_iter)Debug::debugFile() << *(debug_iter) << " ";Debug::debugFile()<< endl; Debug::debugFile().flush();}}
#define DEBUG_PTRVEC(X,M,A) {if (Debug::doDebug(X)){Debug::debugFile()<<M;for(size_t idebug_=0;idebug_<A.size();idebug_++)Debug::debugFile() << *A[idebug_] << " ";Debug::debugFile()<< endl; Debug::debugFile().flush();}}
#define DEBUG_NL(X,Y) {if (Debug::doDebug(X)){Debug::debugFile() << Y;}}

#endif // NDEBUG

