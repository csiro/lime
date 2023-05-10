

#include <iostream>

#include "lime/dijkstra.h"
#include "lime/constants.h"
#include "lime/debug.h"

using namespace lime;
using namespace std;

int main (int argc, const char* argv[])
{
    if (argc > 1)
        Debug::setKey (argv[1]);
    
    size_t num_nodes = 7;
    Dijkstra<int> dijk(num_nodes);

    dijk.addEdge (0, 1, 1);
    dijk.addEdge (0, 2, 3);
    dijk.addEdge (0, 3, 3);
    dijk.addEdge (1, 4, 3);
    dijk.addEdge (1, 3, 2);
    dijk.addEdge (2, 3, 1);
    dijk.addEdge (3, 4, 2);
    dijk.addEdge (3, 6, 2);
    dijk.addEdge (3, 5, 3);
    dijk.addEdge (4, 6, 1);
    dijk.addEdge (4, 5, 1);
    dijk.addEdge (5, 4, 1);
    dijk.addEdge (5, 6, 2);

    if (dijk.findPath (0, 6)) {
        cout << "Found path" << endl;
        size_t curr = 6;
        cout << "Reverse Path is";
        while (curr < num_nodes) {
            cout << " " << curr << " (" << dijk.costTo(curr) << ")";
            curr = dijk.parent(curr);
        }
        cout << endl;
    }
    else {
        cout << "No path" << endl;
    }
    
}


    
