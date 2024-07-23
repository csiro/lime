
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

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
    if (save_vals_)
        vals_.push_back (val);
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

double
Stat::pearsonCorrelation (const Stat* other) const
{
    if (count() != other->count())
        return -2.0f; // Return illegal val for bad input

    double prod_sum = 0.0f;
    for (size_t k = 0; k < count_; k++) {
        prod_sum += vals(k) * other->vals(k);
    }
    double numerator = count() * prod_sum - (sum() * other->sum());

    double multiplier1 = count() * sumSq() - sum() * sum();
    double multiplier2 = count() * other->sumSq() - other->sum() * other->sum();
    double denominator = sqrt (multiplier1 * multiplier2);

    if (denominator == 0.0f)
        return 0.0;

    return numerator / denominator;
}


void
Stat::display (std::ostream& os) const
{
    os << "Stat, mean " << mean() << " sd " << stddev();
}

