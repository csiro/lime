#ifndef LIME_LOCKFILE_H
#define LIME_LOCKFILE_H

/**
 *  Defines a object that handles locking a file for exclusive access
 */

namespace lime {

    class LockFile
    {
    public:
        LockFile(const char* filename);
        virtual ~LockFile();
        void releaseLock();

        void display (std::ostream&) const;

    private:
        int fd_;
        char* lockFilename_;
    };

    std::ostream& operator<< (std::ostream& out, const LockFile& fl);
}

#endif
