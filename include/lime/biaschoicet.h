#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
 *  Templated version of BiasChoice
 *  A biased choice between objects - proportional to a given weight
 *  Can also make the choice inversely proportional
 */

#include <iostream>
#include <list>

#include "lime/rand.h"

namespace lime {
    template <typename ValType>
    class BiasChoiceT : public Displayable
    {
    public:
        BiasChoiceT(int seed) :
            choices_(),
            sumWeights_(0),
            rand_(seed)
        {
        }
    
        void addChoice (ValType val, double weight = 1.0)
        {
            choices_.push_back (ChoicePair(weight,val));
            sumWeights_ += weight;
        }
            
        void removeChoice (ValType target)
        {
            for (
                auto iter = choices_.begin();
                iter != choices_.end();
                ++iter
            ) {
                ValType val = (*iter).second;
                if (val == target) {
                    double weight = (*iter).first;
                    sumWeights_ -= weight;
                    choices_.erase (iter);
                    break;
                }
            }
        }

        size_t numChoices() const {return choices_.size();}
        bool empty() const {return choices_.empty();}
        void clear()
        {
            choices_.clear();
            sumWeights_ = 0;
        }
    
        ValType choose ()
        {
            if (choices_.size() == 0)
                return 0;
            double target = rand_.uniform01() * sumWeights_;
            ValType val{};
            for (
                auto iter = choices_.begin();
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

        ValType inverseChoose ()
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

        void display (std::ostream& out) const override
        {
            out << "Choice of " << choices_.size() << " values";
        }

    private:
        typedef std::pair<double,ValType> ChoicePair;
        typedef std::list<ChoicePair> ChoiceList;
        ChoiceList choices_;
        double sumWeights_;
        Rand rand_;
    };
}
