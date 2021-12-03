
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <iostream>
#include <fcntl.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string.h>

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

#include "lime/fileutil.h"
#include "lime/error.h"

using namespace lime;
using namespace std;

string
lime::unique_filename(string dir_name)
{
    enum {MAX_TRIES = 1000};
    int pid = getpid();
    int count = 1;
        
    string fn_base = dir_name + "/limetmp_" + to_string(pid) + "_";
    string fn = fn_base + to_string(count) + ".tmp";
    //cerr << "Try " << fn << endl;
    int fd = open (fn.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
    while (fd < 0 && errno == EEXIST && count < MAX_TRIES) {
        // the file already exist, try another
        fn = fn_base + to_string(++count) + ".tmp";
        //cerr << "Try " << fn << endl;
        fd = open (fn.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
    }
    if (fd < 0) 
        limeCrash (
            "Can't open unique file in " << dir_name <<
            " after " << MAX_TRIES << " tries"
        );
    // Now close the file, ready for use
    close (fd);
    return fn;
}
