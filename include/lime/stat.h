#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <vector>

#include "lime/displayable.h"

namespace lime {
    
    class Stat : public Displayable
    {
    public:
        Stat(bool save_vals = false) :
            save_vals_(save_vals),
            count_(0),
            sum_(0),
            sumSq_(0),
            vals_()
        {}

        bool save_vals() const {return save_vals_;}
        
        void add (double val);
        int count() const {return count_;}
        double sum() const {return sum_;}
        double sumSq() const {return sumSq_;}
        double mean() const;
        double stddev() const;
        double variance() const;
        
        double vals(size_t k) const {
            if (k >= vals_.size())
                return 0.0f;
            return vals_[k];
        }
        double pearsonCorrelation (const Stat* other) const;

        void display (std::ostream& os = std::cout) const override;
    
    protected:
        bool save_vals_;
        
        int count_;
        double sum_;
        double sumSq_;
        std::vector<double> vals_;
    };
}

