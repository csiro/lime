#ifndef LIME_STAT_H
#define LIME_STAT_H

#include <iostream>

namespace lime {
    
    class Stat
    {
    public:
        Stat() : count_(0), sum_(0), sumSq_(0) {}
        virtual ~Stat() {}

        void add (double val);
        double mean() const;
        double stddev() const;
        double variance() const;

        void display (std::ostream&) const;
    
    protected:
        double count_;
        double sum_;
        double sumSq_;
    };

    std::ostream& operator<< (std::ostream&, const Stat&);
}

#endif
