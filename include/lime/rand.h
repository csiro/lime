#ifndef LIME_RAND_H
#define LIME_RAND_H

#include <iostream>

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
        int getSeed () const {return seed;}
        int generateSeed () {return uniform0n_1(8190);}
        double uniform01 () {return rnd (0);};
        int uniform0n_1 (int n);
        double normal01 ();
        double normal (double mean, double sdev);
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

#endif // RAND_H
