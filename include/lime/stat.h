#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>

#include "lime/displayable.h"

namespace lime {
    
    class Stat : public Displayable
    {
    public:
        Stat() : count_(0), sum_(0), sumSq_(0) {}
        virtual ~Stat() {}

        void add (double val);
        double mean() const;
        double stddev() const;
        double variance() const;

        void display (std::ostream& os = std::cout) const override;
    
    protected:
        int count_;
        double sum_;
        double sumSq_;
    };
}

