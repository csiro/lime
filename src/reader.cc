#include <cassert>
#include <stdlib.h>

#include "lime/debug.h"
#include "lime/error.h"
#include "lime/strutil.h"
#include "lime/reader.h"

#define BUFFER_LEN 10000
#define DELIM " 	"

using namespace std;
using namespace lime;

Reader::Reader (const char* filename) :
    errorStr_(),
    fileStack_(),
    currFrame_(new FileFrame (filename)),
    buffer_(new char [BUFFER_LEN])
{
    DEBUG ('D', "Reading " << filename);
    if (!currFrame_->ok())
        limeCrash ("Couldn't open input file " << filename);
}

Reader::Reader (string filename) :
    errorStr_(),
    fileStack_(),
    currFrame_(new FileFrame (filename.c_str())),
    buffer_(new char [BUFFER_LEN])
{
    DEBUG ('D', "Reading " << filename);
    if (!currFrame_->ok())
        limeCrash ("Couldn't open input file " << filename);
}

Reader::~Reader ()
{
    if (currFrame_ != 0)
        delete currFrame_;
    delete [] buffer_;
}

char* 
Reader::getLine()
{
    while (true) { // Skip comments and blanks
        currFrame_->in_->getline (buffer_, BUFFER_LEN);

        if (currFrame_->in_->gcount() == 0 && !currFrame_->in_->good()) {
            // Pop current file frame off stack
            DEBUG ('D', "End of file");
            if (fileStack_.empty()) {
                return NULL;
            }
            delete currFrame_;
            currFrame_ = fileStack_.front();
            fileStack_.pop_front();
            DEBUG ('D', "Resume file " << currFrame_->filename_);
            continue;
        }
        currFrame_->lineNum_++;
        // Kill DOS return
        if (strlen (buffer_) > 0 && buffer_[strlen (buffer_) - 1] == '\r') {
            buffer_[strlen (buffer_) - 1] = 0;
        }
        DEBUG ('D', currFrame_->lineNum_ << " >" << buffer_);
        LimeTok ltok (buffer_);
        char* nextTok = nextStr(ltok);

        if (nextTok != NULL && *nextTok == '@') {
            // File redirection. Open a new file frame
            fileStack_.push_front (currFrame_);
            currFrame_ = new FileFrame (nextTok + 1);
            if (!currFrame_->ok())
                readerError (
                    this, "Couldn't open redirected file " <<
                    currFrame_->filename_
                );
            DEBUG (
                'D', "Opened redirected file " << currFrame_->filename_
            );
            continue;
        }
        if (nextTok != NULL && *nextTok != '#')
            break;
    }
    return buffer_;
}

bool
Reader::matches (const char* a, const char* b) const
{
    return a != NULL && b != NULL && strcmp (a, b) == 0;
}

double
Reader::nextDouble (LimeTok& ltok) const
{
    char* str = nextStr(ltok);
    if (str == NULL)
        return (double)0;
    return atof (str);
}

long
Reader::nextInt (LimeTok& ltok) const
{
    char* str = nextStr(ltok);
    if (str == NULL)
        return 0;
    return atoi (str);
}

bool
Reader::nextBool (LimeTok& ltok) const
{
    char* str = nextStr(ltok);
    if (str == NULL)
        return false;
    if ((lime::strcasecmp (str, "true") == 0) || matches (str, "1"))
        return true;
    return false;
}

char*
Reader::nextStr (LimeTok& ltok) const
{
    return ltok.nextToken (DELIM);
}

long
Reader::nextTime (LimeTok& ltok) const
{
    char* tok = nextStr(ltok);
    if (tok == NULL)
        return 0;
    LimeTok ltok2 (tok);

    char* hhStr = ltok2.nextToken (":");
    char* mmStr = ltok2.nextToken (":");
    char* ssStr = ltok2.nextToken (":");
    int hh = 0;
    int mm = 0;
    int ss = 0;
    if (hhStr == NULL)
        return 0;
    if (ssStr == NULL || mmStr == NULL) {
        // It is a seconds-only time
        ss = atoi (hhStr);
    }
    else {
        hh = atoi (hhStr);
        mm = atoi (mmStr);
        ss = atoi (ssStr);
    }
    return hh * 3600 + mm * 60 + ss;
}

void
Reader::readerError_ ()
{
    limeCrash (
        errorStr_.str() << " at line " << currFrame_->lineNum_ <<
        " of " << currFrame_->filename_
    );
}


Reader::FileFrame::~FileFrame()
{
    if (in_ != 0) {
        in_->close();
        delete in_;
    }
    if (filename_ != 0)
        delete [] filename_;
}
bool
Reader::FileFrame::open (const char* filename)
{
    DEBUG ('D', "Open file " << filename);
    in_ = new ifstream (filename);
    filename_ = lime::strdup (filename);
    lineNum_ = 0;
    return in_->good();
}

bool
Reader::FileFrame::ok ()
{
    return in_ != 0 && in_->good();
}

