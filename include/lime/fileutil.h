#pragma once


/**
 *  Defines a object that handles locking a file for exclusive access
 */

namespace lime {

    /**
       Return a unique file name. The file will exist and be empty.
       Suitable for use as a temporary file for a process.
       Note: Caller should remove file when no longer required.
    */
        
    std::string unique_filename(std::string dir_name = std::string("."));
}
