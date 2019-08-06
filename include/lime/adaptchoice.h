#pragma once

/**
 *  Multipliers and config items for lns 
 */

#include <iostream>
#include <vector>

#include "lime/adaptcfg.h"
#include "lime/indexchoice.h"
#include "lime/displayable.h"

namespace lime {

    class AdaptChoice : public Displayable
    {
    public:
        /** Create an adapt-choice
            sigma1: Reward for new-best
            sigma2: Reward for new-incumb
            sigma3: Reward for new solution
        */
        AdaptChoice(int numChoice, const lime::AdaptCfg& cfg, int seed);

        void setNumChoice (int numChoice);
        int numChoices() const {return numChoice_;}
    
        /** Choose an index. Updates count.
            Rebalances weights if segmentlen reached
        */
        int choose();
    
        /** What is the current weight (probability) for the method  */
        double weight(int idx) const {return chooser_.weight(idx);}
    
        /** Clear memory */
        void clear();

        /** Increase the score for new best*/
        void score1 (int idx) {score_[idx] += cfg_.sigma1();}
        /** Increase the score for new incumb */
        void score2 (int idx) {score_[idx] += cfg_.sigma2();}
        /** Increase the score for not-seen solution*/
        void score3 (int idx) {score_[idx] += cfg_.sigma3();}

        void updateWeights();

        void display (std::ostream& out) const override;
    
    protected:
        /** The number of choices */
        int numChoice_;
        /** How many times have we been called? */
        int callCount_;
        /** The current score for each weight, from current segment */
        std::vector<double> score_;
        std::vector<short> count_;
        lime::IndexChoice chooser_;
    
        AdaptCfg cfg_;
    };
}
