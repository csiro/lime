
#include <iostream>

#include "lime/numutil.h"

using namespace std;

main ()
{
    vector<int> x = {1, 7, 3, 2, 9, 4, 6, 0, 8, 5};

    auto srt_idx = sort_indices (x);
    
    for (auto i: srt_idx) {
        cout << i << ": " << x[i] << endl;
    }
    cout << endl;
    for (size_t i = 0; i < x.size(); ++i) {
        cout << i << ": " << srt_idx[i] << " " << x[srt_idx[i]] << endl;
    }

    return 0;
}
