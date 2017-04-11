
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <4 Oct 2013 17:02:38>"

#include <iostream>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <unistd.h>

#include <lime/lockfile.h>
#include <lime/error.h>

/** Lock a file for exclusive use */

using namespace lime;

LockFile::LockFile (const char* filename) :
    fd_(0),
    lockFilename_ (new char [strlen (filename) + 10])
{
    sprintf (lockFilename_, "%s.lck", filename);
    
    fd_ = open (lockFilename_, O_WRONLY | O_CREAT | O_EXCL, 0666);
    
    while (fd_ < 0 && errno == EEXIST) {
        // the file already exist; another process is 
        // holding the lock
        limeProgress ("Waiting for lock on file " << filename);
        sleep (1);
        fd_ = open (lockFilename_, O_WRONLY | O_CREAT | O_EXCL, 0666);
    }
    if (fd_ < 0) {
        limeWarning ("File lock failed for file " << filename);
    }
}

LockFile::~LockFile () 
{
    if (fd_ > 0) 
        releaseLock();
    delete [] lockFilename_;
}

void
LockFile::releaseLock()
{
    if (fd_ > 0)
        close (fd_);
    fd_ = 0;
    remove (lockFilename_);
}

void
LockFile::display (std::ostream& os) const
{
    os << "Lockfile " << lockFilename_;
}

