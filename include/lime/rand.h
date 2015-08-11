#ifndef LIME_RAND_H
#define LIME_RAND_H
// 
// 
//                       R A N D . H
//                       ===========
//
// Random number generator class
//

#include <iostream>

namespace lime {

    class Rand
    {
    public:
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

        void display (std::ostream&) const;

    private:
        double rnd (int n);

        int seed;
    
        // Data for rnd
        double* r3;
        double *r30ptr, *r3kptr, *r3ptr;
        double r1, s, t, rmc, rm;
        long iw, i, ic, id, ir, ikt;
    };

    std::ostream& operator<< (std::ostream&, const Rand&);
    
} //namespace

#endif // RAND_H
