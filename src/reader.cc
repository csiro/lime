
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <cassert>
#include <stdlib.h>

#include "lime/debug.h"
#include "lime/error.h"
#include "lime/strutil.h"
#include "lime/reader.h"

#define BUFFER_LEN 100000
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
Reader::getLine(bool skipBlanks, bool skipComments)
{
    while (true) { // Skip comments and (optionally) blanks
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
        std::string nextTokStr = ltok.nextString();
        const char* nextTok = nextTokStr.c_str();

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
        if (nextTok == NULL && !skipBlanks)
            break;
        if (nextTok != NULL && (!skipComments || *nextTok != '#'))
            break;
    }
    return buffer_;
}

bool
Reader::matches (const char* a, const char* b) 
{
    return a != NULL && b != NULL && strcmp (a, b) == 0;
}

void
Reader::rewind()
{
    while (fileStack_.size() > 1) {
        delete currFrame_;
        currFrame_ = fileStack_.front();
        fileStack_.pop_front();
    }
    // Now back in original frame
    currFrame_->rewind();
}

void
Reader::error (string message)
{
    limeCrash (
        message << " at line " << currFrame_->lineNum_ <<
        " of " << currFrame_->filename_
    );
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

void
Reader::FileFrame::rewind ()
{
    if (in_ != 0) {
        if (!in_->good()) {
            open (filename_);
        }
        else {
            in_->seekg (0, in_->beg);
            lineNum_ = 0;
        }
    }
}

