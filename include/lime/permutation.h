#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


/** Visit all permutations of a vector of ints
    Takes a vector of num-values (
    The num-values vector 2 3 2 would generate permutations
    0 0 0
    1 0 0
    0 1 0
    1 1 0
    0 2 0
    1 2 0
    0 0 1
    1 0 1
    0 1 1
    1 1 1
    0 2 1
    1 2 1
 */

#include <vector>
#include <assert.h>

namespace lime
{
    class Permutation
    {
    public:
        Permutation();
        /** numVals gives the maximum value in each position */
        Permutation(std::vector<int> numVals) :
            numVals_(numVals)
        {
        }

        void setNumVals(std::vector<int> numVals) {
            numVals_ = numVals;
        }

        bool first (std::vector<int>& idx) {
            if (numVals_.size() == 0)
                return false;
            idx.resize(numVals_.size(), 0);
            return true;
        }
        bool next (std::vector<int>& idx) {
            unsigned i = 0;
            while (i < numVals_.size()) {
                idx[i]++;
                if (idx[i] >= numVals_[i]) {
                    idx[i] = 0;
                    i++;
                }
                else
                    return true;
            }
            return false;
        }

    private:
        std::vector<int> numVals_;
    };
} 
