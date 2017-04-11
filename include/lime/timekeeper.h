#pragma once

/**
 *  Keeps track of time. Can be used as a count-down timer with a
 *  a given (cpu) time limit, or to simply track cpu usage.
 */

#include <iostream>
#include <sys/times.h>

#include "lime/displayable.h"

namespace lime {

    class TimeKeeper : public Displayable
    {
    public:
        /** Create a TimeKeeper - used to time a process. No time limit
         */
        TimeKeeper();
        /** Create a TimeKeeper - used to time a process,
            with a time limit in seconds
        */
        TimeKeeper(int timeLimitS);
        virtual ~TimeKeeper();

        /** Resets the usage back to zero, and optionally sets a new limit */
        void reset(int newLimit = 0);
        /** Return the elapsed cpu time in seconds */
        double elapsedTimeSecs() const;
        /** If a time limit was set at creation, returns the number of seconds
            left on the clock
        */
        double timeLeftSecs() const;
        /** Has the time limit been reached? */
        bool hasTimeLeft() const;
        /** Does this timer have a time limit? */
        int hasTimeLimit() const {return timeLimitS_ != 0;}
        /** Return the time limit in effect.
            Zero time limit means no time limit
        */
        int timeLimit() const {return timeLimitS_;}
	void setTimeLimit(int timeLimitS) { timeLimitS_ = timeLimitS; }

        void display (std::ostream& os = std::cout) const override;
    
    protected:
        struct tms start_;
        long ticksPerSec_;
        int timeLimitS_;
    };

} //namespace

