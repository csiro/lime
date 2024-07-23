
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "lime/stat.h"
#include "lime/numutil.h"

using namespace std;
using namespace lime;

void
my_assert (string msg, int a, int b)
{
    cout << msg << ": ";
    if (a == b)
        cout << "ok (" << a << ")" << endl;
    else 
        cout << "FAIL! " << a << " should match " << b << endl;
    
}

void
my_assert (string msg, double a, double b)
{
    cout << msg << ": ";
    if (limeDblEqual (a, b))
        cout << "ok (" << a << ")" << endl;
    else 
        cout << "FAIL! " << a << " should match " << b << endl;
}

void
my_assert (string msg, bool a)
{
    cout << msg << ": ";
    if (a)
        cout << "ok" << endl;
    else 
        cout << "FAILED! " << endl;
}

int main()
{
    Stat stat (true);
    Stat stat2 (true);

    limeSetEpsilon (1.0e-3);

    // Data from https://www.scribbr.com/statistics/pearson-correlation-coefficient
    stat.add (3.63f); stat2.add (53.1f);
    stat.add (3.02f); stat2.add (49.7f);
    stat.add (3.82f); stat2.add (48.4f);
    stat.add (3.42f); stat2.add (54.2f);
    stat.add (3.59f); stat2.add (54.9f);
    stat.add (2.87f); stat2.add (43.7f);
    stat.add (3.03f); stat2.add (47.2f);
    stat.add (3.46f); stat2.add (45.2f);
    stat.add (3.36f); stat2.add (54.4f);
    stat.add (3.30f); stat2.add (50.4f);

    my_assert ("Count", stat.count(), 10);
    my_assert ("Sum", stat.sum(), 33.5f);
    my_assert ("Sum2", stat2.sum(), 501.2f);
    my_assert ("SumSq", stat.sumSq(), 113.0432f);
    my_assert ("SumSq2", stat2.sumSq(), 25264.0f);

    double r_val = stat.pearsonCorrelation (&stat2);
    my_assert ("Pearson r-val", r_val, 0.4702);
    
    return 0;
}
