#pragma once

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

        char* getLine();
        bool matches (const char* a, const char* b) const;
        bool isListEnd (const char* str) const {return matches (str, "*END*");}

        // The following assume the line returned by getLine()
        // has been processed using LimeTok ltok (line);
        double nextDouble (LimeTok& ltok) const;
        long nextInt (LimeTok& ltok) const;
        bool nextBool (LimeTok& ltok) const;
        char* nextStr (LimeTok& ltok) const;
        long nextTime (LimeTok& ltok) const;

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

