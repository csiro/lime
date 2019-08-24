
#include <iomanip>

#include "lime/progressbar.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;


bool
ProgressBar::progress (int iter, std::string message, bool newBest)
{
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
        cerr << (p <= proportion ? '#' : '_');
    cerr << "|  " << message << "                          \r";
    lastIter_ = iter;
    
    bool cancel = false;
    if (kbhit()) {
        cancel = true;
        cerr << " Cancelling                                    " << endl;
    }
    return cancel;
}

