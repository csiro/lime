#pragma once

/**
 *  Use an improved (extended) simulated annealing method to
 *  choose whether to accept a sol.
 */

#include <iostream>
#include <string>
#include <math.h>

#include "lime/acceptmeth.h"
#include "lime/debug.h"
#include "lime/constants.h"
#include "lime/rand.h"

namespace lime
{
    template <typename ObjType>
    class SimAnneal : public AcceptMeth<ObjType>
    {
    public:
        SimAnneal (
            double targAccept, double targProb, int seed
        ) :
            AcceptMeth<ObjType>(),
            iter_(0),
            noChangeIter_(0),
            temp_(0),
            tempMult_(0),
            targAccept_(targAccept),
            targProb_(targProb),
            initTemp_(0),
            restarts_(0),
            restartMod_(0),
            rand_(seed)
        {}

        enum {FRAC_NO_CHANGE = 20};

        double temp() const {return temp_;}
        void setTemp (double temp) {
            temp_ = temp;
        }
        double tempMult() const {return tempMult_;}
        void setTempMult (double tempMult) {
            tempMult_ = tempMult;
        }

        void init (ObjType objVal, long numIters, int restarts) override
        {
            noChangeIter_ = 0;
            if (numIters > FRAC_NO_CHANGE)
                noChangeIter_ = numIters / FRAC_NO_CHANGE;
            initTemp_ = temp_ = calcTemp (objVal);
            restarts_ = restarts;
            restartMod_ = (numIters - noChangeIter_) / (restarts_ + 1) + 1;
                                    // +1 so we don't restart on the last iter
            tempMult_ = calcTempMult (restartMod_);
            DEBUG (
                'L', "SA: Initial temp " << temp_ << " mult " << tempMult_ <<
                " restart every " << restartMod_ << " iters"
            )
        }
        
        bool accept (ObjType solCost, ObjType incumbCost) override
        {
            bool accept = false;
            auto delta = (double) (solCost - incumbCost);
            if (delta < 0) {
                accept = true;
            }
            else if (delta < LIME_EPSILON) {
                accept = rand_.coinToss();
            }
            else if (temp_ < LIME_EPSILON) {
                accept = false;
            }
            else if (iter_ < noChangeIter_) {
                accept = false;
            }
            else {
                double acceptThresh = exp (-delta / temp_);
                accept = (rand_.uniform01() < acceptThresh);
            }
            DEBUG (
                'L', "SA: iter " << iter_ << " sol " << solCost <<
                " incumb " << incumbCost << " temp " << temp_ <<
                " accept " << accept
            );
            return accept;
        }
            
        void iter (long iter, ObjType objVal) override
        {
            iter_++;
            if (
                iter > noChangeIter_ &&
                (iter_ - noChangeIter_) % restartMod_ == 0
            ) {
                temp_ = calcTemp (objVal);
                tempMult_ = calcTempMult (restartMod_);
            }
            else if (temp_ > 1.0) {
                if (iter_ >= noChangeIter_)
                    temp_ *= tempMult_;
            }
            else
                temp_ = 1.0;
            DEBUG (
                'l', "    SimAnneal iter " << iter_ << " temp now " << temp_
            );
        }


    protected:
        double calcTemp (ObjType objVal)
        {
            double temp =
                - (targAccept_ * objVal) / log (targProb_);
            if (temp < LIME_EPSILON)
                temp = 1.0;
            return temp;
        }
        double calcTempMult (long numIters)
        {
            // Calc the mult that will get us to temp 1 in numIters_ iters
            // given a starting temperature of temp_
            return exp (- log(temp_) / numIters);
        }

    private:
        long iter_; 	
        long noChangeIter_; 	// How many iters before we can accept increase
        double temp_; 		// The temperature
        double tempMult_;
        double targAccept_;
        double targProb_;
        double initTemp_; 	
        int restarts_;
        int restartMod_;
        lime::Rand rand_;
    };
}
