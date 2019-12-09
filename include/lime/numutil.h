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

/** Are all entries in the array zero? */
bool allZero (const long* arr, int n);

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


