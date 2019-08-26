#pragma once

#include <memory>

namespace lime {
    
    class ProgressListener 
    {
    public:
        ProgressListener(int maxIters = 0) :
            maxIters_(maxIters)
        {
        }

        int maxIters() const {return maxIters_;}
        void setMaxIters (int maxIters) {maxIters_ = maxIters;}
    
        /** Callback for notifying progress.
            Will print before usual iters if newBest is set.
            Return value true means cancel the run
            Return value false means keep going.
        */
        virtual bool progress (
            int iter, std::string message, bool newBest
        ) = 0;
    
    protected:
        int maxIters_;
    };

    using ProgressListenerPtr = std::shared_ptr<ProgressListener>;
}
