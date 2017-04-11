#pragma once

/**
 *  A biased choice between ints. Similar to BiasChoice,
 *  but this object assumes ints will be consecutive,
 *  start at zero, and go to a maximum
 *  This one is optimised for querying and updating the
 *  current value of a weight
 *  This version can also accept -ve weights, and will cope with them.
 */

#include <iostream>
#include <vector>

#include "lime/rand.h"

namespace lime {

    class IndexChoice
    {
    public:
        IndexChoice(int seed, int size, double initialWeight = (double)0.0);

        void setSize(int size, double initialWeight = (double)0.0);
        void setWeight (int val, double weight);
        void removeChoice (int val);
        double getWeight (int index) const {return weight_[index];}
        double sumWeights() const {return sumWeights_;}
        int numChoices() const {return size_;}
        bool empty() const {return sumWeights_ < 1e-3;}
        void clear (double weight = (double)0.0);
    
        int choose ();
        int inverseChoose ();
    
        void display (std::ostream&) const;
    
    private:
        int size_;
        std::vector<double> weight_;
        double sumWeights_;
        double minWeight_;
        Rand rand_;
    };

    std::ostream& operator<< (std::ostream&, const IndexChoice&);
}
