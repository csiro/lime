
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

/** 
 *  A biased choice between ints
*/

#include <assert.h>

#include "lime/biaschoice.h"
#include "lime/numutil.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

BiasChoice::BiasChoice(int seed) :
    choices_(),
    sumWeights_(0),
    rand_(seed)
{
}


void
BiasChoice::addChoice (int val, double weight)
{
    choices_.push_back (ChoicePair(weight,val));
    sumWeights_ += weight;
}

/** Remove the choice with the given val
    (for selection without replacement)
*/
void
BiasChoice::removeChoice (int target)
{
    for (
        ChoiceList::iterator iter = choices_.begin();
        iter != choices_.end();
        ++iter
    ) {
        int val = (*iter).second;
        if (val == target) {
            double weight = (*iter).first;
            sumWeights_ -= weight;
            choices_.erase (iter);
            break;
        }
    }
}

int
BiasChoice::numChoices() const
{
    return choices_.size();
}

void
BiasChoice::clear ()
{
    choices_.clear();
    sumWeights_ = 0;
}

int
BiasChoice::choose () 
{
    if (choices_.size() == 0)
        return 0;
    double target = rand_.uniform01() * sumWeights_;
    int val = 0;
    for (
        ChoiceList::const_iterator iter = choices_.begin();
        iter != choices_.end();
        ++iter
    ) {
        double weight = (*iter).first;
        val = (*iter).second;
        if (target <= weight)
            return val;
        target -= weight;
    }
    // Not supposed to fall through - probably a rounding error,
    // so just return the last one
    return val; 
}

int
BiasChoice::inverseChoose () 
{
    if (choices_.size() == 0)
        return 0;
    
    double theMin = choices_.front().first;
    for (auto ch : choices_)
        if (ch.first <  theMin)
            theMin = ch.first;
    
    if (theMin < 1.0) {
        // Push everyone up to at least 1.0
        sumWeights_ += choices_.size() * (1.0 - theMin);
        for (auto& ch : choices_)
            ch.first += (1.0 - theMin);
        theMin = 1.0;
    }
    double sumInvWeights = 0.0;
    for (auto ch : choices_)
        sumInvWeights += sumWeights_ / ch.first;
    
    DEBUG (
        '5', "  Choosing from " << choices_.size() <<
        " minWgt " << theMin <<
        " sumInvWgt " << sumInvWeights
    );
    double target = rand_.uniform01() * sumInvWeights;
    
    for (auto ch : choices_) {
        double invWeight = sumWeights_ / ch.first;
        DEBUG (
            '5', "    wgt " << ch.first << " invwgt " << invWeight <<
            " target " << target
        );
        if (target <= invWeight) {
            return ch.second;
        }
        target -= invWeight;
    }
    // Not supposed to fall through - probably a rounding error,
    // so just return the last one
    return choices_.back().second;
}




void
BiasChoice::display (ostream& out) const
{
    out << "Choice of " << choices_.size() << " ints";
}

// ------------------------

ostream&
operator<< (ostream& out, const BiasChoice& choice)
{
    choice.display (out);
    return out;
}
