
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/


#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "lime/debug.h"

using namespace std;

char Debug::key_[100];
ofstream* Debug::outfile_ = 0;
string Debug::filename_ = "";
int Debug::startTime_ = 0;

Debug::Debug(const std::string& filename) {Debug::filename_ = filename;}

void Debug::setKey (const char * key)
{
    strcpy (Debug::key_, key);
}

void Debug::setStartTime (int startTime)
{
    Debug::startTime_ = startTime;
}

bool Debug::doDebug (char c)
{
    return strchr (Debug::key_, c) != 0;
}

std::ostream& Debug::debugFile()
{
    if (outfile_ == 0) {
        const char* filename = (filename_ != "")?filename_.c_str():"debug.out";
        const char* envFilename = getenv ("LIME_DEBUG");
        if (envFilename != NULL)
            filename = envFilename;
        outfile_ = new ofstream (filename);
    }
    return *outfile_;
}

/**
   Turn __DATE__ and __TIME__ into an string build id.
   Date is expected to be Mmm dd YYYY
   Time is expected to be hh:mm:ss
*/
string
lime::buildId (string dateStr, string timeStr)
{
    string mStr = dateStr.substr(0, 3);
    string dStr = dateStr.substr(4, 2);
    string yStr = dateStr.substr(9, 2);
        
    unsigned long mo = 0;
    if (mStr.compare("Jan") == 0)
        mo = 0;
    else if (mStr.compare("Feb") == 0)
        mo = 1;
    else if (mStr.compare("Mar") == 0)
        mo = 2;
    else if (mStr.compare("Apr") == 0)
        mo = 3;
    else if (mStr.compare("May") == 0)
        mo = 4;
    else if (mStr.compare("Jun") == 0)
        mo = 5;
    else if (mStr.compare("Jul") == 0)
        mo = 6;
    else if (mStr.compare("Aug") == 0)
        mo = 7;
    else if (mStr.compare("Sep") == 0)
        mo = 8;
    else if (mStr.compare("Oct") == 0)
        mo = 9;
    else if (mStr.compare("Nov") == 0)
        mo = 10;
    else if (mStr.compare("Dec") == 0)
        mo = 11;

    unsigned long dd = (unsigned long)atoi (dStr.c_str());
    unsigned long yy = (unsigned long)atoi (yStr.c_str());
    
    unsigned long hh =
        (unsigned long)atoi(timeStr.substr(0,2).c_str());
    unsigned long mm =
        (unsigned long)atoi(timeStr.substr(3,2).c_str());
    unsigned long ss =
        (unsigned long)atoi(timeStr.substr(6,2).c_str());
    //cout << yy << " " << mo << " " << dd << " " << hh << " " << mm << " " << ss << endl;

    unsigned long build =
        ((((((yy * 12) + mo) * 31) + dd) * 24 + hh) * 60 +  mm) * 60 + ss;
    stringstream str;
    str << hex << build;
    return str.str();
}
        
