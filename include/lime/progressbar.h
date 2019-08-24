#pragma once

#include <iostream>

#include "lime/progresslistener.h"

namespace lime {
    
    class ProgressBar : public lime::ProgressListener
    {
    public:
        ProgressBar(int reportIters = 1, int maxIters = 0) :
            ProgressListener (reportIters, maxIters),
            lastIter_(0)
        {
        }

        bool progress (int iter, std::string message, bool newBest) override;
    
    private:
        int lastIter_;
    };
}
