#pragma once

#include <iostream>
#include <cfloat>
#include <math.h>

#include "lime/displayable.h"

namespace lime {

    /** Class for generating pseudo-random numbers in various distributions. */
    class Rand : public Displayable
    {
    public:

        /** Constructor.
            @param seed seed for the pseud-random number generator.
         */
        Rand (int seed = 0);
        virtual ~Rand ();

        void setSeed (int n);
        static int maxSeed() {return 8190;}
        int getSeed () const {return seed;}
        int generateSeed () {return 1 + uniform0n_1(maxSeed()-1);}
        bool coinToss () {return rnd (0) < 0.5;}
        double uniform01 () {return rnd (0);}
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
            os << "Rand";
        }

    private:
        double rnd (int n);

        int seed;

        // Data for rnd
        double* r3;
        double *r30ptr, *r3kptr, *r3ptr;
        double r1, s, t, rmc, rm;
        long iw, i, ic, id, ir, ikt;
    };

} //namespace

