#pragma once

#include <vector>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort

#include "lime/constants.h"

/** Max and min functions - c is all over the place with these */
template <typename T>
T limeMax (T a, T b)
{
    if (a > b)
        return a;
    return b;
}
template <typename T>
T limeMax (T a, T b, T c)
{
    if (a > b && a > c)
        return a;
    if (b > c)
        return b;
    return c;
}
template <typename T>
T limeMin (T a, T b)
{
    if (a < b)
        return a;
    return b;
}
template <typename T>
T limeMin (T a, T b, T c)
{
    if (a < b && a < c)
        return a;
    if (b < c)
        return b;
    return c;
}

template<typename T> T limeMin (std::vector<T> vec);
template<typename T> T limeMax (std::vector<T> vec);

/** Round a to the nearest r */
int limeRound (int a, int r);
/** Round a up to the nearest r */
int limeRoundUp (int a, int r);
/** Round a up to the nearest r */
int limeRoundDown (int a, int r);
/** Is a within epsilon (= 1e-6) of b? */
bool limeDblEqual (double a, double b);
/** Is a within epsilon (= 1e-6) of 0? */
bool limeIsZero (double a);

/** The epsilon we use for "equality" */
double limeEpsilon();

namespace lime
{
    /** Are all entries in the array zero? */
    bool allZero (const long* arr, int n);

    double cvt_kmph_mps (double kmph);
    double cvt_mps_kmph (double mps);

    // Convert from days+hh:mm:ss to seconds
    double cvt_to_secs (
        double ss, double mm = 0.0, double hh = 0.0, double days = 0.0
    );

    double deg2rad (double deg);
    double rad2deg (double rad);
    
   /** Return the vector of indexes that sort the given vector input
        Vector requires a natural ordering (i.e. operator<)
    */
    template <typename T>
    std::vector<size_t> sort_indices (const std::vector<T> &v)
    {
        // initialize original index locations
        std::vector<size_t> idx(v.size());
        std::iota(idx.begin(), idx.end(), 0);

        // sort indexes based on comparing values in v
        std::sort(idx.begin(), idx.end(),
                  [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

        return idx;
    }

    /* Distribute @param total units evenly as possible
       amongst the entries of @param buckets.
       (The maximum difference between bucket entries is 1)
       E.g. if buckets has size 4 and total is 10, buckets is returned as
       [ 3 3 2 2 ]
       Valid for any integer/unsigned type T
    */

    template <typename T>
    void
    distribute (T total, std::vector<T>& buckets)
    {
        T size = (T) buckets.size();
        if (size == 0)
            return; // Let the caller sort this out.
        T base = total / size;
        T remainder = total - (size * base);
        assert (remainder < size);
        T check = 0;
        for (size_t k = 0; k < buckets.size(); k++) {
            if (remainder > 0) {
                buckets[k] = base + 1;
                remainder--;
                check += base + 1;
            }
            else {
                buckets[k] = base;
                check += base;
            }
        }
        assert (remainder == 0 && check == total);
    }
}
