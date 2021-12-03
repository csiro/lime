#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
 *  A biased choice between ints - proportional to a given weight
 *  Can also make the choice inversely proportional
 */

#include <iostream>
#include <list>

#include "lime/rand.h"

namespace lime {
    
    class BiasChoice
    {
    public:
        BiasChoice(int seed);
    
        void addChoice (int val, double weight = 1.0);
        void removeChoice (int val);
        int numChoices() const;
        bool empty() const {return numChoices() == 0;}
        void clear ();
    
        int choose ();
        int inverseChoose ();
    
        void display (std::ostream&) const;
    
    private:
        typedef std::pair<double,int> ChoicePair;
        typedef std::list<ChoicePair> ChoiceList;
        ChoiceList choices_;
        double sumWeights_;
        Rand rand_;
    };

    std::ostream& operator<< (std::ostream&, const BiasChoice&);
}
