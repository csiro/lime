#include <ctime>
#include <iostream>
#include <cstdlib>

#include "lime/dateutil.h"

using namespace std;

time_t
lime::dateToTimeT (
    int year, int month, int day,
    int hours, int mins, int secs
)
{
    tm tmp = tm();
    tmp.tm_sec = secs;
    tmp.tm_min = mins;
    tmp.tm_hour = hours;
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    tmp.tm_isdst = -1;
    return mktime(&tmp);
}

void
lime::timeTtoDate (
    time_t the_date, int& year, int& month, int& day,
    int& hours, int& mins, int& secs
)
{
    tm* tmp = localtime(&the_date);
    secs = tmp->tm_sec;
    mins = tmp->tm_min;
    hours = tmp->tm_hour;
    day = tmp->tm_mday;
    month = tmp->tm_mon + 1 ;
    year = tmp->tm_year + 1900;
}

void
lime::timeTtoDate (
    time_t the_date, int& year, int& month, int& day
)
{
    tm* tmp = localtime(&the_date);
    day = tmp->tm_mday;
    month = tmp->tm_mon + 1 ;
    year = tmp->tm_year + 1900;
}


time_t
lime::badTime()
{
    return time_t(-1);
}

time_t
lime::now() {
    return time(0);
}

long
lime::daysDiff (time_t earlyTime, time_t lateTime)
{
    double sec = difftime(lateTime, earlyTime);
    long days = static_cast<long>(sec / (60 * 60 * 24));
    return days;
}
    
    

