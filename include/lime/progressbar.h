#pragma once

#include <iostream>

#include "lime/progresslistener.h"
#include "lime/timekeeper.h"

namespace lime {
    
    class ProgressBar : public lime::ProgressListener
    {
    public:
        ProgressBar(int maxIters = 0, double freq = 0.5) :
            ProgressListener (maxIters),
            freq_(freq),
            lastIter_(0),
            lastReport_(0.0),
            timer_()
        {
        }

        double freq() const {return freq_;}
        void setFreq (double freq) {freq_ = freq;}
        
        bool progress (int iter, std::string message, bool newBest) override;
    
    private:
        double freq_;
        int lastIter_;
        double lastReport_;
        TimeKeeper timer_;
    };
}
