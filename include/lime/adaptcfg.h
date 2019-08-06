#pragma once


/**
 *  Multipliers and config items for adapative LNS
 */

#include <iostream>

#include "lime/displayable.h"

class ImproveMeth;

namespace lime {

    class AdaptCfg : public Displayable
    {
    public:
        /**
           sigma1: Reward for new-best
           sigma2: Reward for new-incumb
           sigma3: Reward for new solution
        */       
        AdaptCfg (
            double sigma1, double sigma2, double sigma3, double learnRate,
            int segmentLen
        ) :
            sigma1_(sigma1),
            sigma2_(sigma2),
            sigma3_(sigma3),
            learnRate_(learnRate),
            segmentLen_(segmentLen)
        {
        }
        AdaptCfg (const AdaptCfg& other) :
            sigma1_(other.sigma1_),
            sigma2_(other.sigma2_),
            sigma3_(other.sigma3_),
            learnRate_(other.learnRate_),
            segmentLen_(other.segmentLen_)
        {
        }
            
        double sigma1() const {return sigma1_;}
        void setSigma1 (double sigma1) {
            sigma1_ = sigma1;
        }
        double sigma2() const {return sigma2_;}
        void setSigma2 (double sigma2) {
            sigma2_ = sigma2;
        }
        double sigma3() const {return sigma3_;}
        void setSigma3 (double sigma3) {
            sigma3_ = sigma3;
        }
        double learnRate() const {return learnRate_;}
        void setLearnRate (double learnRate) {
            learnRate_ = learnRate;
        }
        int segmentLen() const {return segmentLen_;}
        void setSegmentLen (int segmentLen) {
            segmentLen_ = segmentLen;
        }
        
        void display (std::ostream& out) const override
        {
            out << "sigma1 " << sigma1_ <<
                "sigma2 " << sigma2_ << 
                "sigma3 " << sigma3_ <<
                "learnRate " << learnRate_ <<
                "segmentLen " << segmentLen_;
        }
                
                
    private:
        // The parameters controlling feature list selection
        double sigma1_;
        double sigma2_;
        double sigma3_;
        double learnRate_;
        int segmentLen_;
    };
}
