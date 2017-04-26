#pragma once

#include <sstream>

extern bool limeQuiet;
extern std::stringstream _limeErrorLine;

void _limeLog (std::stringstream& str);
void _limeWarning (std::stringstream& str);
void _limeCrash (std::stringstream& str);
void _limeProgress (std::stringstream& str);
void _limeAssert (bool assertion, const char* file, int line);

#define limeLog(X) {_limeErrorLine << X.str(); _limeLog(_limeErrorLine);}
#define limeWarning(X) {_limeErrorLine << X; _limeWarning(_limeErrorLine);}
#define limeCrash(X) {_limeErrorLine << X; _limeCrash(_limeErrorLine);}
#define limeProgress(X) {_limeErrorLine << X; _limeProgress(_limeErrorLine);}
#ifdef NDEBUG
#define limeAssert(X) {if(X){}} // Use the expression to keep the compiler happy
#else
#define limeAssert(X) {_limeAssert(X,__FILE__,__LINE__);}
#endif
