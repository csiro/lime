
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include <assert.h>

#include "lime/adaptchoice.h"
#include "lime/numutil.h"
#include "lime/debug.h"

using namespace std;
using namespace lime;

#define MIN_FEAT_WEIGHT 0.1

AdaptChoice::AdaptChoice (int numChoice, const AdaptCfg& cfg, int seed) :
    Displayable(),
    numChoice_(numChoice),
    callCount_(0),
    score_(numChoice, 0.0),
    count_(numChoice, 0),
    chooser_(seed, numChoice),
    cfg_(cfg)
{
    clear();
}

void
AdaptChoice::setNumChoice (int numChoice)
{
    numChoice_ = numChoice;
    if (numChoice == 0)
        return;
    score_.resize (numChoice, 0.0);
    count_.resize (numChoice, 0);
    chooser_.setSize (numChoice);
    clear();
}

void
AdaptChoice::clear()
{
    callCount_ = 0;
    for (int i = 0; i < numChoice_; i++) {
        chooser_.setWeight (i, (double) 1.0 / numChoice_);
    }
    if (numChoice_ > 0) {
        std::fill (score_.begin(), score_.end(), 0.0);
        std::fill (count_.begin(), count_.end(), 0);
    }
}

/** Choose an index, but don't update count
    Rebalance if at interval len
 */
int 
AdaptChoice::suggest ()
{
    if (callCount_ == cfg_.segmentLen()) {
        // Time to rebalance
        updateWeights();
    }
        
    int which = 0;
    if (numChoice_ > 1)
        which = chooser_.choose();
    return which;
}

/** Choose an index. Updates count.
    Rebalance if at interval len
 */
int 
AdaptChoice::choose()
{
    int which = suggest();
    use(which);
    return which;
}

void AdaptChoice::updateWeights()
{
    DEBUG ('l',"    updateWeights in AdaptChoice");
    DEBUG_ARR (
        'l', "      scores are ", score_, numChoice_
    );
    DEBUG_ARR (
        'l', "      counts are ", count_, numChoice_
    );
    double normalise_wgt = 1.0f;
    if (cfg_.normalise()) {
        normalise_wgt = 0.0f;
        for (int i = 0; i < numChoice_; i++) {
            normalise_wgt += score_[i];
        }
        normalise_wgt /= cfg_.segmentLen();
    }
    for (int i = 0; i < numChoice_; i++) {
        double oldWeight = chooser_.weight(i);
        double newWeight = 0;
        if (count_[i] == 0)
            newWeight = oldWeight;
        else 
            newWeight = score_[i] / (normalise_wgt * count_[i]);
        // Replace the weight
        double w = 
            (1.0 - cfg_.learnRate()) * oldWeight +
            cfg_.learnRate() * newWeight;
        DEBUG (
            'l', "      i " << i << " old " << oldWeight << " new " << newWeight
        );
        if (w < MIN_FEAT_WEIGHT)
            w = MIN_FEAT_WEIGHT;
        chooser_.setWeight (i, w);
    }
    callCount_ = 0;
    std::fill (score_.begin(), score_.end(), 0.0);
    std::fill (count_.begin(), count_.end(), 0);
    DEBUG ('l', "      Choice is now " << chooser_);
}

void
AdaptChoice::display (std::ostream& out) const
{
    out << " callCount: " << callCount_;
    out << " score";
    for (int i = 0; i < numChoice_; i++)
        out << " " << score_[i];
    out << " count ";
    for (int i = 0; i < numChoice_; i++)
        out << " " << count_[i];
    out << " weight ";
    for (int i = 0; i < numChoice_; i++)
        out << " " << chooser_.weight(i) / chooser_.sumWeights();
}


