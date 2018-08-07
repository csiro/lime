
#include <stdlib.h>
#include <stdio.h>

#include "lime/box.h"
#include "lime/rand.h"
#include "lime/dig.h"

using namespace std;
using namespace lime;

int
main()
{
    Rand rand (0);
    Dig dig ("box.dig");
    
    Box b (20, 20, 40, 40);
    
    for (int i = 0; i < 20; i++) {
        double x = (double) rand.uniform0n_1(60);
        double y = (double) rand.uniform0n_1(60);
        double dx = (double) rand.uniform0n_1(15) + 5;
        double dy = (double) rand.uniform0n_1(15) + 5;
        Box b2 (x, y, x + dx, y + dy);
        int c = 2;
        if (b.overlaps (&b2))
            c = 3;
        dig.box (&b, 1);
        dig.box (&b2, c);
        dig.waitAndWipe();
    }
    Box b2 (25, 10, 35, 50);
    int c = 2;
    if (b.overlaps (&b2))
        c = 3;
    dig.box (&b, 1);
    dig.box (&b2, c);
    dig.waitAndWipe();

    cout << "Wrote file box.dig" << endl;
    return 0;
}
