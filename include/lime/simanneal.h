#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


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
#include "lime/error.h"
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
        {
            if (targAccept < 1)
                limeWarning ("simanneal.h: targAccept should be > 1");
        }

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
            restartMod_ = 1 + numIters / (restarts_ + 1);
                                    // +1 so we don't restart on the last iter
            tempMult_ = calcTempMult (restartMod_);
            DEBUG (
                'L', "SA: Using obj " << objVal <<
                " and numiters " << numIters <<
                " initial temp " << temp_ <<
                " mult " << tempMult_ <<
                " restart every " << restartMod_ << " iters" <<
                " no change for " << noChangeIter_
            )
        }
        
        bool accept (ObjType solCost, ObjType incumbCost) override
        {
            bool accept = false;
            double acceptThresh = 0;
            double delta = (double) (solCost - incumbCost);
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
                acceptThresh = exp (-delta / temp_);
                accept = (rand_.uniform01() < acceptThresh);
            }
            DEBUG (
                'L', "SA: iter " << iter_ << " sol " << solCost <<
                " incumb " << incumbCost << " temp " << temp_ <<
                " delta " << delta << 
                " acceptThresh " << acceptThresh << 
                " accept " << accept
            );
            return accept;
        }
            
        void iter (long iter, ObjType objVal) override
        {
            iter_++;
            if ((iter_ + 1) % restartMod_ == 0) {
                temp_ = calcTemp (objVal);
                tempMult_ = calcTempMult (restartMod_);
            }
            else {
                temp_ *= tempMult_;
                if (temp_ < 1.0)
                    temp_ = 1.0;
            }
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
            assert (numIters > noChangeIter_);
            return exp (- log(temp_) / (numIters - noChangeIter_));
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
