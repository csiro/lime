#include <cmath>

#include "lime/numutil.h"

/** Lime numeric utilities */

#define LIME_EPSILON (1e-6)

int
limeMax (int a, int b)
{
    if (a > b)
        return a;
    return b;
}
    
int
limeMin (int a, int b)
{
    if (a < b)
        return a;
    return b;
}

double
limeMax (double a, double b)
{
    if (a > b)
        return a;
    return b;
}

double
limeMin (double a, double b)
{
    if (a < b)
        return a;
    return b;
}

long
limeMax (long a, long b)
{
    if (a > b)
        return a;
    return b;
}
    
long
limeMin (long a, long b)
{
    if (a < b)
        return a;
    return b;
}

long
limeMax (long a, long b, long c)
{
    if (a > b && a > c)
        return a;
    if (b > c)
        return b;
    return c;
}
    
long
limeMin (long a, long b, long c)
{
    if (a < b && a < c)
        return a;
    if (b < c)
        return b;
    return c;
}

template<typename T>
T limeMin (std::vector<T> vec)
{
    if (vec.size() == 0)
        return 0;
    T theMin = vec[0];
    for (auto i : vec)
        if (i < theMin)
            theMin = i;
    return theMin;
}


/** Round a to the nearest r */
int
limeRound (int a, int r)
{
    bool negate = false;
    if (a < 0) {
        negate = true;
        a = -a;
    }
    int val = 0;
    int m = a % r;
    if (m == 0)
        val = a;
    else if (m <= r/2)
        val = a - m;
    else
        val = a + r - m;
    return negate ? -val : val;
}

/** Round a up to the nearest r */
int
limeRoundUp (int a, int r)
{
    if (a < 0) 
        return -limeRoundDown (-a, r);
    int m = a % r;
    if (m == 0)
        return a;
    return a + r - m;
}

/** Round a down to the nearest r */
int
limeRoundDown (int a, int r)
{
    if (a < 0) 
        return -limeRoundUp (-a, r);
    int m = a % r;
    if (m == 0)
        return a;
    return a - m;
}

bool
limeDblEqual (double a, double b)
{
    return (fabs (a - b) < LIME_EPSILON);
}

bool limeIsZero (double a)
{
    return (fabs (a) < LIME_EPSILON);
}


bool
allZero (const long* arr, int n)
{
    for (int i = 0; i < n; i++)
        if (arr[i] != 0)
            return false;
    return true;
}
