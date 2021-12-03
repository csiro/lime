#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <exception>
#include <stdexcept>

// Define a singleton LimeError class
class LimeErrorImpl
{
public:
    LimeErrorImpl() :
        isOpen_(false),
        quiet_(false),
        truncate_(false),
        crashThrowsExcept_(false),
        errorStream_(),
        fileName_(""),
        log_(&std::cerr),
        logFile_()
    {
    }
    ~LimeErrorImpl()
    {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }

    bool quiet() const {return quiet_;}
    void setQuiet (bool quiet) {quiet_ = quiet;}

    bool truncate() const {return truncate_;}
    void setTruncate (bool truncate) {
        truncate_ = truncate;
    }
    
    bool crashThrowsExcept() const {return crashThrowsExcept_;}
    void setCrashThrowsExcept (bool crashThrowsExcept) {
        crashThrowsExcept_ = crashThrowsExcept;
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
    bool crashThrowsExcept_;
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
    static void setCrashThrowsExcept(bool crashThrowsExcept) {
        getImpl()->setCrashThrowsExcept(crashThrowsExcept);
    }
    static bool crashThrowsExcept() {
        return getImpl()->crashThrowsExcept();
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
    static void _limeAssert2(bool assertion, const char* file, int line);

private:
    static LimeErrorImpl* getImpl() {
        if (impl_ == nullptr) {
            impl_ =  std::unique_ptr<LimeErrorImpl>(new LimeErrorImpl());
        }
        return impl_.get();
    }
    static std::string timeStr ();
    
    static std::unique_ptr<LimeErrorImpl> impl_;
};
    
#define limeWarning(X) {LimeError::errorStream() << X; LimeError::warning();}
#define limeCrash(X) {LimeError::errorStream() << X << std::endl << "at " << __FILE__ << " line " << __LINE__; LimeError::crash();}
#define limeProgress(X) {LimeError::errorStream() << X; LimeError::progress();}

#define limeAssert(X) {LimeError::_limeAssert((X),__FILE__,__LINE__);}
#define limeAssert2(X, Y) {LimeError::errorStream() << Y; LimeError::_limeAssert2((X), __FILE__,__LINE__);}
