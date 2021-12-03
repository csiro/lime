#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <iostream>
#include <random>
#include <climits>
#include <cfloat>

#include "lime/displayable.h"

namespace lime {

    /** Class for generating pseudo-random numbers in various distributions. */
    class LimeRand : public Displayable
    {
    public:

        /** Constructor.
            @param seed seed for the pseud-random number generator.
         */
        LimeRand (int seed = 0);

        void setSeed (int n);
        static int maxSeed() {return INT_MAX;}
        int getSeed () const {return seed_;}
        int generateSeed () {return 1 + uniform0n_1(maxSeed()-2);}
        bool coinToss () {return rnd () < 0.5;}
        double uniform01 () {return rnd ();}
        int uniform0n_1 (int n);
        double normal01 ();
        double normal (double mean, double sdev);
        double logNormal (double mean, double sdev) {
            return exp (normal (mean, sdev));
        }
        double truncNormal (double mean, double sdev, double lb, double ub = DBL_MAX);
        double standardExponential ();
        double exponential (double mean);

        void display (std::ostream& os = std::cout) const override
        {
            os << "LimeRand(" << seed_ <<")";
        }

    private:
        double rnd() {
            return u01_(gen_);
        }
        
        //std::mt19937 gen_;
        std::ranlux24_base gen_;
        std::uniform_real_distribution<> u01_;
        std::normal_distribution<double> n01_;
        std::exponential_distribution<double> exp1_;
        int seed_;
    };

} //namespace

