#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/** System utils  */

/* Note: requires C++11 */
#include <chrono>
#include <thread>


namespace lime
{
    void sleep_secs (size_t secs)
    {
        std::this_thread::sleep_for(std::chrono::seconds(secs));
    }

    void sleep_millis (size_t millisecs)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecs));
    }
}

