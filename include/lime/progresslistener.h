#pragma once

#include <memory>

namespace lime {
    
    class ProgressListener 
    {
    public:
        ProgressListener(int reportIters = 1, int maxIters = 0) :
            reportIters_(reportIters > 0 ? reportIters : 1),
            maxIters_(maxIters)
        {
        }

        int reportIters() const {return reportIters_;}
        int maxIters() const {return maxIters_;}
    
        void setIters (int reportIters, int maxIters)
        {
            reportIters_ = reportIters > 0 ? reportIters : 1;
            maxIters_ = maxIters;
        }
    
        /** Callback for notifying progress.
            Will print before usual iters if newBest is set.
            Return value true means cancel the run
            Return value false means keep going.
        */
        virtual bool progress (
            int iter, std::string message, bool newBest
        ) = 0;
    
    protected:
        int reportIters_;
        int maxIters_;
    };

    using ProgressListenerPtr = std::shared_ptr<ProgressListener>;
}
