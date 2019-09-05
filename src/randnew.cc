// 
// 
//                       R A N D . C C
//                       =============
//
// Routine for generating random numbers.
//

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <iterator>

#include "lime/randnew.h"

using namespace std;

/*
  Generate random numbers using c++ generators
 */

using namespace lime;

LimeRand::LimeRand (int seed) :
    gen_(seed),
    u01_(0.0, 1.0),
    n01_(0.0, 1.0),
    exp1_(1.0),
    seed_(seed)
{
    if (seed == 0)
        setSeed(0);
}


void LimeRand::setSeed (int seed)
{
    seed_ = seed == 0 ? (int) time (0) : seed;
    gen_.seed(seed);
}

double
LimeRand::normal01 () 
{
    return n01_(gen_);
}

int
LimeRand::uniform0n_1 (int n)
{
    return (int) (n * uniform01());
}

double
LimeRand::normal (double mean, double sdev)
{
    return normal01() * sdev + mean;
}

double
LimeRand::truncNormal (double mean, double sdev, double lb, double ub)
{
    double val = normal (mean, sdev);
    if (val < lb)
        val = lb;
    if (val > ub)
        val = ub;
    return val;
}

double
LimeRand::standardExponential ()
{
    return exp1_(gen_);
}

double
LimeRand::exponential (double mean)
{
    return standardExponential() * mean;
}

