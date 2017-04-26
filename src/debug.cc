
#include <string.h>
#include <stdlib.h>

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
#ifndef NDEBUG
    debugFile() << "Debugging: Key " << Debug::key_ << endl;
#endif
}

void Debug::setStartTime (int startTime)
{
    Debug::startTime_ = startTime;
#ifndef NDEBUG
    debugFile() << "Debugging: Start Time " << Debug::startTime_ << endl;
#endif
}

bool Debug::doDebug (char c)
{
    return strchr (Debug::key_, c) != 0;
}

std::ostream& Debug::debugFile()
{
    if (outfile_ == 0) {
        const char* filename = (filename_ != "")?filename_.c_str():"debug.out";
        const char* envFilename = getenv ("ATOMIC_DEBUG");
        if (envFilename != NULL)
            filename = envFilename;
        outfile_ = new ofstream (filename);
    }
    return *outfile_;
}

