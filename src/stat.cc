#include <cassert>
#include <cmath>

#include "lime/stat.h"

using namespace std;
using namespace lime;

void
Stat::add (double val)
{
    count_++;
    sum_ += val;
    sumSq_ += val * val;
}

double
Stat::mean() const
{
    if (count_ == 0)
        return 0;
    return sum_ / count_;
}

double
Stat::stddev() const
{
    return sqrt (variance());
}

double
Stat::variance() const
{
    double var = 0;
    if (count_ > 1) {
        var = sumSq_ / count_ - mean() * mean();
        if (var < 0) // Handle rounding probs
            var = 0;
    }
    return var;
}

void
Stat::display (std::ostream& os) const
{
    os << "Stat, mean " << mean() << " sd " << stddev();
}

