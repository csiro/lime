#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/



/**
 *  Defines a object that handles locking a file for exclusive access
 */

namespace lime {

    /**
       Return a unique file name. The file will exist and be empty.
       Suitable for use as a temporary file for a process.
       Note: Caller should remove file when no longer required.
    */
        
    extern std::string unique_filename(std::string dir_name = std::string("."));

    /** Check the filename is valid - ie. not empty and not "none" */
    extern bool isFilename (std::string filename);
}
