#ifndef LIME_NUMUTIL_H
#define LIME_NUMUTIL_H

/** Max and min functions - c is all over the place with these */
int limeMax (int a, int b);
int limeMin (int a, int b);
double limeMax (double a, double b);
double limeMin (double a, double b);
long limeMax (long a, long b);
long limeMax (long a, long b, long c);
long limeMin (long a, long b);
long limeMin (long a, long b, long c);
/** Round a to the nearest r */
int limeRound (int a, int r);
/** Round a up to the nearest r */
int limeRoundUp (int a, int r);
/** Round a up to the nearest r */
int limeRoundDown (int a, int r);
/** Is a within epsilon (= 1e-6) of b? */
bool limeDblEqual (double a, double b);

/** Are all entries inthe array zero? */
bool allZero (const long* arr, int n);

#endif
