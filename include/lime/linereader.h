#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <list>

#include "lime/rand.h"
#include "lime/limetok.h"

namespace lime {

    class LineReader
    {
    public:
        LineReader(std::string filename);

        /** Returns false at EOF */
        bool getLine (
            std::string& line, bool skipBlanks = true, bool skipComments = true
        );

        std::string currFilename() const {return currFrame_->filename_;}
        int currLineNum() const {return currFrame_->lineNum_;}

        // '#' automatically treated as comment delim
        // Add another one
        void addCommentString (std::string comment) {
            comments_.push_back (comment);
        }

        // Calls limecrash
        void error (std::string message);
        
    protected:
        struct FileFrame
        {
            std::ifstream in_;
            std::string filename_;
            int lineNum_;

            FileFrame (std::string filename) :
                in_(filename),
                filename_(filename),
                lineNum_(0)
            {
            }
            bool ok () const {return in_.good();}
        };
        using FileFramePtr = std::shared_ptr<FileFrame>;
        using FileStack = std::list<FileFramePtr>;

        // Does the string starting at k match a comment?
        bool isComment (std::string str, int k);

        /** Stack of open files (not including current) */
        FileStack fileStack_;
    
        /** The current file frame */
        FileFramePtr currFrame_;

        std::list<std::string> comments_;
    };

} //namespace

