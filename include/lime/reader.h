#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

#include "lime/rand.h"
#include "lime/limetok.h"

// Use with readerError (ReaderPtr,"Message " << stuff);
#define readerError(X,Y) {(X)->errorStr_ << Y; (X)->readerError_();}

namespace lime {

    class Reader
    {
    public:
        Reader(const char* filename);
        Reader(std::string filename);
        virtual ~Reader();

        /** Returns NULL at EOF */
        char* getLine(bool skipBlanks = true);
        static bool matches (const char* a, const char* b);
        bool isListEnd (const char* str) const {return matches (str, "*END*");}

        // Rewind to start of file
        void rewind();

        // Called by readerError()
        void error (std::string message);
        // Called by readerError()
        void readerError_ ();

        /** Buffer for error reports */
        std::stringstream errorStr_;
        
    protected:
        struct FileFrame
        {
            std::ifstream* in_;
            const char* filename_;
            int lineNum_;

            FileFrame () :
                in_(0),
                filename_(0),
                lineNum_(0)
            {
            }
            FileFrame (const char* filename) :
                in_(0),
                filename_(0),
                lineNum_(0)
            {
                open (filename);
            }
            FileFrame (const FileFrame& other) :
                in_(other.in_),
                filename_(other.filename_),
                lineNum_(other.lineNum_)
            {
            }
            virtual ~FileFrame();
            bool open (const char* filename);
            bool ok ();
            void rewind ();
        };

        typedef std::list<FileFrame*> FileStack;

        /** Stack of open files (not including current) */
        FileStack fileStack_;
    
        /** The current file frame */
        FileFrame* currFrame_;

        /** Buffer for reading */
        char* buffer_;
    };

} //namespace

