
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/


#include <iterator>
#include <functional>
#include <algorithm>

#include <assert.h>

#include "lime/shuffle.h"

using namespace std;
using namespace lime;


void
Shuffle::shuffle (int n)
{
    for (size_t k = 0; k < n; k++) {
        order_.add (k, rand_.uniform01());
    }
    order_.doSort();
    shuffled_ = true;
}


