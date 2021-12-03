
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

/** 
 *  A biased choice between ints. Similar to BiasChoice,
 *  but this object assumes ints will be consecutive,
 *  start at zero, and go to a maximum
 *  This one is optimised for querying and updating the
 *  current value of a weight
 *  This version can also accept -ve weights, and will cope with them.
*/


#include <assert.h>

#include "lime/indexchoice.h"
#include "lime/constants.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

IndexChoice::IndexChoice(int seed, int size, double initialWeight) :
    size_(size),
    weight_(size),
    sumWeights_(0.0),
    minWeight_(LIME_BIG_DOUBLE),
    rand_(seed)
{
    clear (initialWeight);
}


void
IndexChoice::setSize (int size, double initialWeight)
{
    size_ = size;
    if (size == 0)
        return;
    weight_.reserve(size);
    clear (initialWeight);
}

void
IndexChoice::setWeight (int val, double weight)
{
    sumWeights_ -= weight_[val]; // Replace current value
    weight_[val] = weight;
    sumWeights_ += weight;
    if (weight < minWeight_)
        minWeight_ = weight;
}

/** Remove the choice with the given val
    (for selection without replacement)
*/
void
IndexChoice::removeChoice (int target)
{
    sumWeights_ -= weight_[target];
    weight_[target] = 0.0;
}

void
IndexChoice::clear (double wgt)
{
    sumWeights_ = size_ * wgt;
    minWeight_ = wgt;
    std::fill (weight_.begin(), weight_.end(), wgt);
}

int
IndexChoice::choose () 
{
    if (minWeight_ < 0.0) {
        // Push everyone up to zero
        sumWeights_ += size_ * (-minWeight_);
        for (int i = 0; i < size_; i++)
            weight_[i] -= minWeight_;
        minWeight_ = 0.0;
    }
    if (size_ == 0)
        return 0;
    double target = rand_.uniform01() * sumWeights_;
    DEBUG ('8', "      Chooser: Sumwgt " << sumWeights_ << " targ " << target);
    for (int i = 0; i < size_; i++) {
        DEBUG ('8', "        Chooser: wgt " << i << ": " << weight_[i]);
        if (target <= weight_[i])
            return i;
        target -= weight_[i];
    }
    // Not supposed to fall through - probably a rounding error,
    // so just return the last one
    DEBUG ('8', "        Chooser: fell through..");
    return size_ - 1; 
}

/** Make a choice _inversely_ proportional to the weight of each choice */
int
IndexChoice::inverseChoose () 
{
    if (minWeight_ < 1.0) {
        // Push everyone up to at least 1.0
        sumWeights_ += size_ * (-minWeight_ + 1.0);
        for (int i = 0; i < size_; i++)
            weight_[i] += (1.0 - minWeight_);
        minWeight_ = 1.0;
    }
    
    if (size_ == 0)
        return 0;

    DEBUG_NL ('4', " InvChoice");
    double sumInvWeights = 0.0;
    for (int i = 0; i < size_; i++) {
        assert (weight_[i] > 1.0 - LIME_EPSILON);
        DEBUG_NL (
            '4', " " << i << " " << weight_[i] <<
            " " << sumWeights_ / weight_[i]
        );
        sumInvWeights += sumWeights_ / weight_[i];
    }
    double target = rand_.uniform01() * sumInvWeights;

    for (int i = 0; i < size_; i++) {
        double invWeight = sumWeights_ / weight_[i];
        if (target <= invWeight) {
            DEBUG ('4', " " << i << " " << weight_[i] << " " << minWeight_);
            return i;
        }
        target -= invWeight;
    }
    // Not supposed to fall through - probably a rounding error,
    // so just return the last one
    return size_ - 1; 
}

void
IndexChoice::display (ostream& out) const
{
    out << "IndexChoice";
    for (int i = 0; i < size_; i++)
        out << " [" << i << "," << weight_[i] << "]";
}

// ------------------------

ostream&
lime::operator<< (ostream& out, const IndexChoice& choice)
{
    choice.display (out);
    return out;
}
