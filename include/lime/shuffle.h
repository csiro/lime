#pragma once

/**
   Return the indices of an array shuffled into random order
*/

#include "lime/rand.h"

namespace lime
{
    class Shuffle
    {
    public:
        Shuffle(int seed = 0, int arraysSize = 0);
        virtual ~Shuffle();

        /** Shuffle indices as set up at construction */
        void shuffle();
        /** Shuffle indices up to n */
        void shuffle(int n);
    
        int operator[](int i) const {return index_[i];}

        int get (int i) const {return index_[i];}

    private:
        int arraySize_;
        int* index_;
        double* order_;
        Rand rand_;
    };
} 
