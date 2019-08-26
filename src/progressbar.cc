
#include <iomanip>

#include "lime/progressbar.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;


bool
ProgressBar::progress (int iter, std::string message, bool newBest)
{
    // Only display according to frequency selected, or for new best
    double elapsed = timer_.elapsedTimeSecs();
    if (newBest || elapsed > lastReport_ + freq_) {
        lastReport_ = elapsed;
    
        DEBUG ('a', "Progress: " << iter << " " << message);
        if (iter > 0) 
            cerr << "\r " << "\e[5C" << setw(5) << iter;
        else {
            cerr << "\r " << "\e[5C" << setw(5) << "";
            iter = lastIter_;
        }

        double proportion = -1.0;
        if (maxIters_ > 0) 
            proportion = (double)iter / maxIters_;
    
        cerr << " |";
        for (double p = 0; p <= 1.0; p += 0.05) 
            cerr << (p < proportion ? '#' : '_');
        cerr << "|  " << message << "\e[0K\r";
        lastIter_ = iter;
    }
    
    bool cancel = false;
    if (kbhit()) {
        cancel = true;
        cerr << " Cancelling\e[0K" << endl;
    }
    return cancel;
}

