#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/**
   Return the indices of an array shuffled into random order
*/

#include "lime/rand.h"
#include "lime/sortpairt.h"

namespace lime
{
    class Shuffle
    {
    public:
        Shuffle(int seed = 0, int arraySize = 0) :
            rand_(seed),
            n_(arraySize),
            order_(),
            shuffled_(false)
        {
            if (n_ > 0)
                shuffle (n_);
        }

        /** Shuffle indices as set up at construction */
        void shuffle()
        {
            shuffle (n_);
        }
        
        /** Shuffle indices up to n */
        void shuffle(int n);
    
        int operator[](int i) {return order_[i];}

        int get (int i) {return order_.get(i);}

    private:
        Rand rand_;
        size_t n_;
        SortPairT<size_t> order_;
        bool shuffled_;
    };
} 
