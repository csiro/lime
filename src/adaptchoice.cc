
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

#define MIN_FEAT_WEIGHT 0.05

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
    if (callCount_ >= cfg_.segmentLen()) {
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
    DEBUG ('4',"    updateWeights in AdaptChoice");
    DEBUG_ARR (
        '4', "      scores are ", score_, numChoice_
    );
    DEBUG_ARR (
        '4', "      counts are ", count_, numChoice_
    );
    if (cfg_.normalise()) {
        // Relies on weights summing to 1.0
        if (!limeDblEqual (chooser_.sumWeights(), 1.0f))
            chooser_.normalise();
    };
    DEBUG ('4', "      Choice starts " << chooser_);
    
    double sum_score = 0.0f;
    double sum_wgt = 0.0f;
    for (int i = 0; i < numChoice_; i++) {
        if (count_[i] > 0 && !limeIsZero(chooser_.weight(i))) {
            // Always normalise by count
            score_[i] /= count_[i];
            if (score_[i] < MIN_FEAT_WEIGHT)
                score_[i] = MIN_FEAT_WEIGHT;
            sum_score += score_[i];
            sum_wgt += chooser_.weight(i);
        }
    }
    
    double normalise_wgt = 1.0f;
    if (cfg_.normalise() && sum_wgt > 0.0f)
        normalise_wgt = sum_score / sum_wgt;
    DEBUG (
        '4', "      sum_score " << sum_score <<
        " sum_wgt " << sum_wgt <<
        " normalise_wgt " << normalise_wgt
    );

    for (int i = 0; i < numChoice_; i++) {
        double oldWeight = chooser_.weight(i);
        // If wgt started at 0, leave it there...
        if (limeIsZero(oldWeight))
            continue;
        
        double newWeight = 0;
        if (count_[i] == 0)
            newWeight = oldWeight;
        else 
            newWeight = score_[i] / normalise_wgt;
        // Replace the weight
        double w = 
            (1.0 - cfg_.learnRate()) * oldWeight +
            cfg_.learnRate() * newWeight;
        DEBUG (
            '4', "      i " << i << " old " << oldWeight << " new " << newWeight
        );
        // Enforce min weight
        if (w < MIN_FEAT_WEIGHT)
            w = MIN_FEAT_WEIGHT;
        chooser_.setWeight (i, w);
    }
    callCount_ = 0;
    std::fill (score_.begin(), score_.end(), 0.0);
    std::fill (count_.begin(), count_.end(), 0);
    DEBUG ('4', "      Choice is now " << chooser_);
}

void
AdaptChoice::display (std::ostream& out) const
{
    out << " callCount " << callCount_;
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


