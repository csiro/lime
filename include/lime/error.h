#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// Define a singleton LimeError class
class LimeErrorImpl
{
public:
    LimeErrorImpl() :
        isOpen_(false),
        quiet_(false),
        truncate_(false),
        errorStream_(),
        fileName_(""),
        log_(&std::cerr),
        logFile_()
    {
    }

    bool quiet() const {return quiet_;}
    void setQuiet (bool quiet) {quiet_ = quiet;}

    bool truncate() const {return truncate_;}
    void setTruncate (bool truncate) {
        truncate_ = truncate;
    }
    
    std::string fileName() {return fileName_;}
    void setFileName (std::string fileName) {
        fileName_ = fileName;
        if (isOpen_) {
            if (logFile_.is_open()) {
                logFile_.close();
                log_ = &std::cerr;
            }
            isOpen_ = false;
        }
    }

    std::ostream& log();
    std::stringstream& errorStream() {return errorStream_;}

private:
    bool tryOpenFile (std::string fn);
    
    bool isOpen_;
    bool quiet_;
    bool truncate_;
    std::stringstream errorStream_;
    std::string fileName_;
    std::ostream* log_;
    std::ofstream logFile_;
};

class LimeError
{
public:
    static void setQuiet(bool quiet) {
        getImpl()->setQuiet(quiet);
    }
    static bool quiet() {
        return getImpl()->quiet();
    }
    static void setTruncate(bool truncate) {
        getImpl()->setTruncate(truncate);
    }
    static bool truncate() {
        return getImpl()->truncate();
    }

    static std::string fileName() {return getImpl()->fileName();}
    static void setFileName (std::string fileName) {
        getImpl()->setFileName(fileName);
    }

    static std::ostream& log() {
        return getImpl()->log();
    }
    static std::stringstream& errorStream() {return getImpl()->errorStream();}

    // Each of these assumes message is already written to errorStream();
    static void warning();
    static void crash();
    static void progress ();
    static void _limeAssert(bool assertion, const char* file, int line);

private:
    static LimeErrorImpl* getImpl() {
        if (impl_ == NULL) {
            impl_ = new LimeErrorImpl();
        }
        return impl_;
    }
    static std::string timeStr ();
    
    static LimeErrorImpl* impl_;
};
    
#define limeWarning(X) {LimeError::errorStream() << X; LimeError::warning();}
#define limeCrash(X) {LimeError::errorStream() << X; LimeError::crash();}
#define limeProgress(X) {LimeError::errorStream() << X; LimeError::progress();}


#ifdef NDEBUG
#define limeAssert(X) {if(X){}} // Use the expression to keep the compiler happy
#else
#define limeAssert(X) {LimeError::assert((X),__FILE__,__LINE__);}
#endif
