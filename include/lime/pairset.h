#pragma once

/**
   A set with <int,double> pairs, with natural order of the double.
   
   PairSet my_set;
   
   my_set.insert (make_pair (an_index, a_double));
   for (auto iter : my_set) {
       // This will return the index with the lowest double
       int idx = (*iter).first;
   }
 */

#include <set>
#include <utility>
#include <assert.h>

namespace lime
{
    using IntDblPair = std::pair<int,double>;

    struct PairSetComp
    {
        bool operator() (const IntDblPair& a, const IntDblPair& b) const {
            return a.second < b.second;
        };
        
    };
    
    using PairSet = std::set<IntDblPair,PairSetComp>;
} 
