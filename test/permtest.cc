
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "lime/permutation.h"

using namespace std;
using namespace lime;

main()
{
    vector<int> numVals = {2, 3, 2, 3};

    Permutation perm (numVals);
    vector<int> idx;
    
    for (bool ok = perm.first(idx); ok; ok = perm.next(idx)) {
        for (unsigned i = 0; i < idx.size(); i++) 
            cout << idx[i] << " ";
        cout << endl;
    }
}
