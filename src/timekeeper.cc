/** Implement the "location" methods */

#include <unistd.h>
#include <math.h>

#include "lime/timekeeper.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

TimeKeeper::TimeKeeper () :
    start_(),
    ticksPerSec_(sysconf(_SC_CLK_TCK)),
    timeLimitS_(0)
{
    reset();
}

TimeKeeper::TimeKeeper (int timeLimit) :
    start_(),
    ticksPerSec_(sysconf(_SC_CLK_TCK)),
    timeLimitS_(timeLimit)
{
    reset();
}

TimeKeeper::~TimeKeeper ()
{
}

void
TimeKeeper::reset(int newLimit) 
{
    times(&start_);
    if (newLimit > 0)
        timeLimitS_ = newLimit;
}


double
TimeKeeper::elapsedTimeSecs() const
{
    struct tms curr;
    times(&curr);

    return (double)(curr.tms_utime - start_.tms_utime) / ticksPerSec_;
}

long
TimeKeeper::elapsedTimeTics() const
{
    struct tms curr;
    times(&curr);

    return (long) (curr.tms_utime - start_.tms_utime);
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

