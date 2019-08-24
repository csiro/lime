#pragma once

/** Control a whirlygig a bit better
    Will only update the whirlygig every freq [0.1] seconds
 */

#include "lime/timekeeper.h"
#include "lime/strutil.h"

namespace lime
{
    class Whirl
    {
    public:
        Whirl(bool usePbdq = false, double freq = 0.1) :
            timer_(),
            freq_(freq),
            usePbdq_(usePbdq),
            lastSecs_(0),
            lastChar_(' '),
            count_(0)
        {}

        char next() {
            double elapsed = timer_.elapsedTimeSecs();
            if (elapsed - lastSecs_ > freq_) {
                count_++;
                lastSecs_ = elapsed;
                lastChar_ =
                    (usePbdq_ ? pbdqWhirlygig (count_) : whirlygig (count_));
            }
            return lastChar_;
        }
            
    private:
        TimeKeeper timer_;
        double freq_;
        bool usePbdq_;
        double lastSecs_;
        char lastChar_;
        int count_;
    };
} 
