
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

/** Implement the "location" methods */

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include <math.h>

#include "lime/timekeeper.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

TimeKeeper::TimeKeeper () :
    start_(clock()),
    timeLimitS_(0)
{
}

TimeKeeper::TimeKeeper (int timeLimit) :
    start_(clock()),
    timeLimitS_(timeLimit)
{
}

TimeKeeper::~TimeKeeper ()
{
}

void
TimeKeeper::reset(int newLimit) 
{
    start_ = clock();
    if (newLimit > 0)
        timeLimitS_ = newLimit;
}


double
TimeKeeper::elapsedTimeSecs() const
{
    return (double)(clock() - start_) / CLOCKS_PER_SEC;
}

clock_t
TimeKeeper::elapsedTimeTics() const
{
    return clock() - start_;
}



double
TimeKeeper::timeLeftSecs() const
{
    return timeLimitS_ - elapsedTimeSecs();
}

bool
TimeKeeper::hasTimeLeft() const
{
    return !hasTimeLimit() || elapsedTimeSecs() < (double)timeLimitS_;
}

void
TimeKeeper::display (ostream& os) const
{
    os << "Elapsed time " << elapsedTimeSecs() << " secs";
}

