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

        char nextChar() {
            count_++;
            return (usePbdq_ ? pbdqWhirlygig (count_) : whirlygig (count_));
        }
        char next() {
            double elapsed = timer_.elapsedTimeSecs();
            //std::cout << elapsed << std::endl;
            if (elapsed - lastSecs_ > freq_) {
                lastSecs_ = elapsed;
                lastChar_ = nextChar();
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
