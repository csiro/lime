#include <cmath>

#include "lime/numutil.h"

/** Lime numeric utilities */

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

bool
limeIsZero (double a)
{
    return (fabs (a) < LIME_EPSILON);
}

double
limeEpsilon()
{
    return LIME_EPSILON;
}

namespace lime
{
    bool
    allZero (const long* arr, int n)
    {
        for (int i = 0; i < n; i++)
            if (arr[i] != 0)
                return false;
        return true;
    }

    double
    cvt_kmph_mps (double kmph)
    {
        return kmph * 1000.0 / 3600.00;
    }
    double
    cvt_mps_kmph (double mps)
    {
        return mps * 3600.00 / 1000.0;
    }

    double
    cvt_to_secs (double ss, double mm, double hh, double days)
    {
        return ss + 60.0 * (mm + 60.0 * (hh + 24.0 * days));
    }

    double deg2rad (double deg)
    {
        const double halfCirc = M_PI / 180;
        return deg * halfCirc;            
    }

    double rad2deg (double rad)
    {
        const double halfCirc = 180 / M_PI;
        return rad * halfCirc;            
    }
    
}
