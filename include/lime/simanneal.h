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
    private:
        constexpr static double frozen = 0.001f;
        
    public:
        SimAnneal (
            double targAccept, double targProb, double fracNoChange, int seed
        ) :
            AcceptMeth<ObjType>(),
            iter_(0),
            noChangeIter_(0),
            temp_(0),
            tempMult_(0),
            targAccept_(targAccept),
            targProb_(targProb),
            fracNoChange_(fracNoChange),
            initTemp_(0),
            restarts_(0),
            restartMod_(0),
            rand_(seed)
        {
            if (targAccept < 1)
                limeWarning ("simanneal.h: targAccept should be > 1");
        }

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
            noChangeIter_ = numIters * fracNoChange_;
            initTemp_ = temp_ = calcTemp (objVal);
            restarts_ = restarts;
            restartMod_ = 1 + numIters / (restarts_ + 1);
            tempMult_ = calcTempMult (restartMod_);
            DEBUG (
                '3', "SA: Using obj " << objVal <<
                " and numiters " << numIters <<
                " initial temp " << temp_ <<
                " mult " << tempMult_ <<
                " restart every " << restartMod_ << " iters" <<
                " no change for " << noChangeIter_ << " iters"
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
            else if (delta < limeEpsilon()) {
                accept = rand_.coinToss();
            }
            else if (limeLessEq (temp_, frozen)) {
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
                '3', "SA: iter " << iter_ << " sol " << solCost <<
                " incumb " << incumbCost << " temp " << temp_ <<
                " delta " << delta << 
                " acceptThresh " << acceptThresh << 
                " accept " << accept
            );
            return accept;
        }
            
        void iter (long callingIter, ObjType bestObjVal) override
        {
            iter_++;
            if ((iter_) % restartMod_ == 0) {
                DEBUG ('3', "    Restart");
                temp_ = calcTemp (bestObjVal);
                tempMult_ = calcTempMult (restartMod_);
            }
            else if (iter_ == noChangeIter_) {
                // Set the temp based on the current obj
                DEBUG ('3', "    Finished no-change period. Recalc temp");
                temp_ = calcTemp (bestObjVal);
                if (restartMod_> noChangeIter_) 
                    tempMult_ = calcTempMult (restartMod_ - noChangeIter_);
            }
            else {
                temp_ *= tempMult_;
                if (temp_ < frozen)
                    temp_ = frozen;
            }
            DEBUG (
                '3', "    SimAnneal iter " << iter_ << " temp now " << temp_
            );
        }


    protected:
        double calcTemp (ObjType objVal)
        {
            if (limeIsZero(targProb_))
                return frozen;
            double temp =
                - (targAccept_ * objVal) / log (targProb_);
            if (temp < limeEpsilon())
                temp = 1.0;
            return temp;
        }
        double calcTempMult (long numIters)
        {
            // Calc the mult that will get us to temp 0.001 in numIters iters
            // given a starting temperature of temp_
            return exp (log(frozen/temp_) / numIters);
        }

    private:
        long iter_; 	
        long noChangeIter_; 	// How many iters before we can accept increase
        double temp_; 		// The temperature
        double tempMult_;
        double targAccept_;
        double targProb_;
        double fracNoChange_;
        double initTemp_; 	
        int restarts_;
        int restartMod_;
        lime::Rand rand_;
    };
}
