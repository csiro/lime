#pragma once

#include "lime/displayable.h"

/**
 *  Defines a object that handles locking a file for exclusive access
 */

namespace lime {

    class LockFile : public Displayable
    {
    public:
        LockFile(const std::string filename, bool useLockfile = true);
        virtual ~LockFile();
        void releaseLock();

        void display (std::ostream& os = std::cout) const override;

    private:
        int fd_;
        std::string lockFilename_;
    };
}

