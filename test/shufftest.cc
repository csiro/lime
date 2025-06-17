
#include <iostream>

#include "lime/shuffle.h"

using namespace std;
using namespace lime;

int
main ()
{
    Shuffle shuff1;

    size_t n = 10;
    shuff1.shuffle (10);
    for (size_t k = 0; k < n; k++)
        cout << shuff1[k] << " " << shuff1.get(k) << endl;

    cout << endl;
    Shuffle shuff2 (0, n);
    for (size_t k = 0; k < n; k++)
        cout << shuff2[k] << " " << shuff2.get(k) << endl;

    return 0;
}
