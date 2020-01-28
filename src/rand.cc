// 
// 
//                       R A N D . C C
//                       =============
//
// Routine for generating random numbers.
//

#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <time.h>

#include "lime/rand.h"

/*	Portable uniform random number generator.
 *	A portable, good and moderately fast random number generator
 *	programmed by R. Brent (ANU), 26/ 10/ 72.
 *	When called with n = 0 rnd returns a random number
 *	uniformly distributed in (0, 1) (including 0 but not 1). The
 *	generator may be initialised by calling with non-zero n
 *	(otherwise a default initialisation with n = 8190 is used).
 *
 *	If the floating point word has a fraction of iw bits, the
 *	algorithm returns x(n) / (2 ** iw), where
 *	x(n) = x(n - 1) + x(n - 127) modulo 2 ** iw
 *	Since 1 + x + x ** 127 is primitive, modulo 2, the period is
 *	at least 2 ** 127 - 1 > 10 ** 38 (see Knuth, The Art of
 *	Computer Programming, Vol. 2, 1969, pp. 26, 32 - 34 and 464).
 *	x(n) is stored as r3 = x(n) / (2 ** iw).
 *
 *	The number 127 may be replaced throughout by 22, 60, 63, 153
 *	or 532  (see Ziegler and Brillhart, On Primitive Trinomials
 *	(mod 2), Inform. Contr. 13 (1968), 541 - 554 and 14 (1969),
 *	566 - 569). Suggested values are 60 if the table size or
 *	initialisation time is critical, and 532 if the degree of
 *	randomness is critical.
 *
 *	Restrictions:-
 *
 *	(1) iw > 12;
 *	(2) 17 * 8190 does not overflow in integer arithmetic;
 *	(3) a binary computer with reasonable floating point arithmetic
 *	is used.
 */

using namespace lime;

#define K 532
#define ZERO 0.0
#define ONE 1.0
#define TWO 2.0
#define HALF 0.5
#define TWOM6 0.015625

Rand::Rand (int seed_) :
    seed(0),
    r3(0),
    r30ptr(0),
    r3kptr(0),
    r3ptr(0),
    r1(TWO),
    s(ZERO),
    t(ONE),
    rmc(ONE),
    rm(0),
    iw(-1),
    i(0),
    ic(0),
    id(0),
    ir(0),
    ikt(0)
{
    r3 = new double [K];
    std::fill (r3, r3 + K, 0);
    setSeed (seed_);
}

Rand::~Rand()
{
    delete [] r3;
}


void Rand::setSeed (int seed_)
{
    seed = seed_ ? seed_ : 1 + ((int) time (0) % (maxSeed()-1));
    rnd (seed);
}

#include <iostream>
#include <iterator>
using namespace std;

double Rand::rnd(int n)
{
    // Test if initialisation is required.
    if((r1 >= ONE) || (n != 0)) {
        /*
        cout << "Rand seed = " << n << endl << "r3 " << endl;
        copy(r3, r3+K, ostream_iterator<double>(cout, " "));
        cout << endl;
        cout << "r1 " << r1 << endl;
        cout << "s " << s << endl;
        cout << "t " << t << endl;
        cout << "rmc " << rmc << endl;
        cout << "rm " << rm << endl;
        cout << "iw " << iw << endl;
        cout << "i " << i << endl;
        cout << "ic " << ic << endl;
        cout << "id " << id << endl;
        cout << "ir " << ir << endl;
        cout << "ikt " << ikt << endl;
        */

	// Initialisation is required. See if iw etc. have been
	// determined.
        if(iw <= 0) {
            // Determine fraction length iw, etc.
            do {
                iw++; 
                t = HALF * t;
                r1 = s;
                s += t;
            } while((s > r1) && (s < ONE)) ;
            ikt = (iw - 1) / 12;
            ic = iw - 12 * ikt;
            for (id = 1, i = 0; i < 13 - ic; i++)
                id = 2 * id;

	    // Compute rmc = 2 ** (-ic) exactly.
            for(i = 0; i < ic; i++) 
                rmc = HALF * rmc;
            
            // The following constant is 2 ** (-12) and must be exact.
            rm = TWOM6 * TWOM6;
        }
 	// Initialise r3 pointers.
        r30ptr = r3;
        r3kptr = r3 + K - 1;
        r3ptr = r3kptr;

        
 	// Determine starting value for small generator.
        ir = (n > 0 ? n : -n) % 8190 + 1;
        
 	// Initialise r3[K-1], ..., r3[0]
        do {
            for(r1 = ZERO, i = 0; i < ikt; i++) {
                // Generate random integer in [0, 8191).
                ir = (17 * ir) % 8191;
                // Add 12 random bits to r1.
                r1 = (r1 + (double)(ir / 2)) * rm;
            }
            ir = (17 * ir) % 8191;
            
            // Add last ic random bits to r1.
            r1 = (r1 + (double)(ir / id)) * rmc;
            *r3ptr-- = r1;
        } while(r3ptr > r30ptr);
        r3ptr--;
    }
    // Generate next random number
    if(r3ptr < r30ptr)
        r3ptr = r3kptr;
    
    // Add last and oldest saved random numbers.
    t = r1 + *r3ptr;
    
    // Reduce modulo one making sure arithmetic is exact.
    if(t >= ONE)
        t = (r1 - HALF) + (*r3ptr - HALF);
    r1 = t;
    
    // Save for future use; update the pointer.
    *r3ptr-- = r1;
    
    // Return the random number generated.
    return(r1);
}

/* 
       Uniform random number generator
       Converted from the FORTRAN.

*/
//
//       ALGORITHM 712, COLLECTED ALGORITHMS FROM ACM.
//       THIS WORK PUBLISHED IN TRANSACTIONS ON MATHEMATICAL SOFTWARE,
//       VOL. 18, NO. 4, DECEMBER, 1992, PP. 434-435.
//
//  The function returns a normally distributed pseudo-random
//  number with zero mean and unit variance.  Calls are made to a
//  function subprogram Uniform01() which must return independent random
//  numbers uniform in the interval (0,1).
//
//  The algorithm uses the ratio of uniforms method of A.J. Kinderman
//  and J.F. Monahan augmented with quadratic bounding curves.
//

double
Rand::normal01 () 
{
    static const double S = 0.449871;
    static const double T = -0.386595;
    static const double A = 0.19600;
    static const double B = 0.25472;
    static const double R1 = 0.27597;
    static const double R2 = 0.27846;

//  Generate P = (u,v) uniform in rectangle enclosing acceptance region
    double U, V;
    while (1) {
 	U = uniform01();
	V = uniform01();
	V = 1.7156 * (V - 0.5);
//      Evaluate the quadratic form
	double X  = U - S;
	double Y  = fabs(V) - T;
	double Q  = X*X + Y*(A*Y - B*X);
//      Accept P if inside inner ellipse
	if (Q < R1) 
            break;
//      Reject P if outside outer ellipse
	if (Q > R2) 
	    continue;
//      Reject P if outside acceptance region
	if (V*V > -4.0*log(U)*U*U) 
	    continue;
	break;
    }
//  Return ratio of P's coordinates as the normal deviate
    return V/U;
}

int
Rand::uniform0n_1 (int n)
{
    return (int) (n * uniform01());
}

double
Rand::normal (double mean, double sdev)
{
    return normal01() * sdev + mean;
}

double
Rand::truncNormal (double mean, double sdev, double lb, double ub)
{
    double val = normal (mean, sdev);
    if (val < lb)
        val = lb;
    if (val > ub)
        val = ub;
    return val;
}

double
Rand::standardExponential ()
{
    // Copied from STATLIB.
    // Original source:
    //     Ahrens, J.H. and Dieter, U.
    //     Computer Methods for Sampling from the
    //     Exponential and Normal Distributions.
    //     Comm. ACM, 15,10 (Oct. 1972), 873 - 882.
    //   All statement numbers correspond to the steps of algorithm
    //   'SA' in the above paper (slightly modified implementation).
    // 
    //   Modified by Barry W. Brown, Feb 3, 1988 to use RANF instead of
    //   SUNIF.  The argument IR thus goes away.
    // 

    static double q[8] = {
	0.6931472,0.9333737,0.9888778,0.9984959,0.9998293,0.9999833,0.9999986,1.0
    };
    long i;
    double sexpo,a,u,ustar,umin;
    double *q1 = q;

    a = 0.0;
    u = uniform01();
    goto S30;
 S20:
    a += *q1;
 S30:
    u += u;
    if(u <= 1.0) goto S20;
    u -= 1.0;
    if(u > *q1) goto S60;
    sexpo = a+u;
    return sexpo;
 S60:
    i = 1;
    ustar = uniform01();
    umin = ustar;
 S70:
    ustar = uniform01();
    if(ustar < umin) umin = ustar;
    i += 1;
    if(u > *(q+i-1)) goto S70;
    sexpo = a+umin**q1;
    return sexpo;
}

double
Rand::exponential (double mean)
{
    return standardExponential() * mean;
}

/*
#include <iostream.h>
main ()
{
    Rand rand (1234);
    int i;
    for (i = 0; i < 100; i++)
        cout << rand.uniform0n_1 (1000000) << endl;
    for (i = 0; i < 100; i++)
        cout << (int) floor (rand.Normal (1000.0, 100.0)) << endl;
    for (i = 0; i < 100; i++)
        cout << (int) floor (rand.Exponential (1000.0)) << endl;
}
*/    

