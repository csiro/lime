#pragma once

#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

namespace lime {
    
    time_t
    dateToTimeT (
        int year, int month, int day,
        int hours = 0, int mins = 0, int secs = 0
    );
    void
    timeTtoDate (
        time_t the_date, int& year, int& month, int& day,
        int& hours, int& mins, int& secs
    );
    void
    timeTtoDate (
        time_t the_date, int& year, int& month, int& day
    );

    time_t badTime();
    time_t now();
    long daysDiff (time_t earlyTime, time_t lateTime);
}

