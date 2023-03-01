
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <cassert>
#include <stdlib.h>

#include "lime/debug.h"
#include "lime/error.h"
#include "lime/strutil.h"
#include "lime/linereader.h"

// Use space and tab as default delim
constexpr const char* DELIM = " 	";

using namespace std;
using namespace lime;

LineReader::LineReader (string filename) :
    fileStack_(),
    currFrame_(std::make_shared<FileFrame> (filename)),
    comments_({ string("#") })
{
    DEBUG ('D', "Reading " << filename);
    if (!currFrame_->ok())
        limeCrash ("Couldn't open input file " << filename);
}

bool
LineReader::getLine (string& line, bool skipBlanks, bool skipComments)
{
    while (true) { // Skip comments and (optionally) blanks
        std::getline (currFrame_->in_, line);
        if (!currFrame_->in_.good()) {
            // Pop current file frame off stack
            DEBUG ('D', "End of file");
            if (fileStack_.empty()) {
                return false;
            }
            currFrame_ = fileStack_.front();
            fileStack_.pop_front();
            DEBUG ('D', "Resume file " << currFrame_->filename_);
            continue;
        }
        currFrame_->lineNum_++;
        DEBUG ('D', currFrame_->lineNum_ << " >" << line << "<");
        // find first non-blank
        int k = 0;
        while (k < line.length() && line[k] == ' ')
            k++;
        if (k < line.length() && line[k] == '@') {
            // File redirection. Open a new file frame
            fileStack_.push_front (currFrame_);
            currFrame_ = make_shared<FileFrame> (line.substr(k+1));
            if (!currFrame_->ok())
                error (
                    string ("Couldn't open redirected file ") +
                    currFrame_->filename_
                );
            DEBUG (
                'D', "Opened redirected file " << currFrame_->filename_
            );
            continue;
        }
        // Kill comments
        if (skipComments) {
            // Kill rest of line from the first comment char
            for (size_t kk = k; kk < line.length(); kk++) {
                if (isComment (line, kk)) {
                    line.erase (kk);
                    break;
                }
            }
        }
        DEBUG ('D', currFrame_->lineNum_ << " >" << line << "<");
        if (k < line.length() || !skipBlanks)
            return true;
    }
}

bool
LineReader::isComment (std::string str, int k)
{
    for (string cmnt : comments_) {
        if (cmnt == str.substr (k, cmnt.length()))
            return true;
    }
    return false;
}


void
LineReader::error (string message)
{
    limeCrash (
        message << " at line " << currFrame_->lineNum_ <<
        " of " << currFrame_->filename_
    );
}
