
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/


#include <iterator>
#include <functional>
#include <algorithm>

#include <assert.h>

#include "lime/shuffle.h"

using namespace std;
using namespace lime;

struct InOrder : public std::binary_function<int, int, bool>
{
    double* order_;
    InOrder (double* order) : order_(order) {}
    virtual ~InOrder () {}
    bool operator()(int i, int j) {
        return order_[i] < order_[j];
    }
};

Shuffle::Shuffle (int seed, int n) :
    arraySize_(n),
    index_(0),
    order_(0),
    rand_(seed)
{
    if (arraySize_ > 0) {
        index_ = new int[arraySize_];
        order_ = new double[arraySize_];
        shuffle();
    }
}

Shuffle::~Shuffle ()
{
    if (index_ != 0) 
        delete [] index_;
    if (order_ != 0) 
        delete [] order_;
}

void
Shuffle::shuffle ()
{
    shuffle (arraySize_);
}

void
Shuffle::shuffle (int n)
{
    if (n > arraySize_) {
        if (arraySize_ > 0) {
            delete [] index_;
            delete [] order_;
        }
        arraySize_ = n;
        index_ = new int[n];
        order_ = new double[n];
    }
        
    for (int i = 0; i < n; i++) {
        index_[i] = i;
        order_[i] = rand_.uniform01();
    }
    
    std::sort (index_, index_ + n, InOrder (order_));
}

