
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <iostream>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <string.h>

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif


#include <lime/lockfile.h>
#include <lime/error.h>

/** Lock a file for exclusive use */

using namespace lime;

/** Very strange useLockfile parameter allows caller to not really use
    lockfile. Makes coding with optional locking easier
*/
LockFile::LockFile (std::string filename, bool useLockfile) :
    fd_(0),
    lockFilename_ (filename + ".lck")
{
    if (useLockfile) {
        fd_ = open (lockFilename_.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
    
        while (fd_ < 0 && errno == EEXIST) {
            // the file already exist; another process is 
            // holding the lock
            limeProgress ("Waiting for lock on file " << filename);
#ifdef _MSC_VER
            _sleep (1);
#else
            sleep(1);
#endif
            fd_ = open (lockFilename_.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
        }
        if (fd_ < 0) {
            limeWarning ("File lock failed for file " << filename);
        }
    }
}

LockFile::~LockFile () 
{
    if (fd_ > 0) 
        releaseLock();
}

void
LockFile::releaseLock()
{
    if (fd_ > 0)
        close (fd_);
    fd_ = 0;
    remove (lockFilename_.c_str());
}

void
LockFile::display (std::ostream& os) const
{
    os << "Lockfile " << lockFilename_;
}

