

#include <iostream>

#include "lime/pwl.h"

using namespace lime;
using namespace std;




int main ()
{
    PiecewiseLinear pwl;

    pwl.add (0, 1);

    cout << "Phase 1. pwl is " << pwl << endl;
    cout << "pwl -1: " << pwl.valueAt (-1) << endl;
    cout << "pwl  0: " << pwl.valueAt (0) << endl;
    cout << "pwl  1: " << pwl.valueAt (1) << endl;
    
    pwl.add (1, 2);
    pwl.add (2, 10);
    pwl.add (3, 4);
    pwl.add (4, 44);
    pwl.add (4, 100);
    pwl.add (5, 200);
    pwl.add (10, 300);

    cout << "Phase 2. pwl is " << pwl << endl;
    for (double x = -0.5; x < 11; x += 0.5) {
        cout << "pwl " << x << ": " << pwl.valueAt (x) << endl;
    }
}


    
