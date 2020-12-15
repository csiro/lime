
#include <iostream>
#include <fstream>

#include "lime/fileutil.h"

using namespace std;
using namespace lime;

int
main (int argc, char* argv[])
{
    string dir_name = ".";
    if (argc > 1) 
        dir_name = argv[1];

    cout << "Using dir_name " << dir_name << endl;
    
    string fn1 = unique_filename (dir_name);
    cout << "Filename 1 is " << fn1 << endl;
    ofstream file1 (fn1);
    file1 << fn1 << endl;

    string fn2 = unique_filename (dir_name);
    cout << "Filename 2 is " << fn2 << endl;
    ofstream file2 (fn2);
    file2 << fn2 << endl;

    string fn3 = unique_filename (dir_name);
    cout << "Filename 3 is " << fn3 << endl;
    ofstream file3 (fn3);
    file3 << fn3 << endl;

    cout << "Do this later:" << endl;
    cout << "rm " << fn1 << " " << fn2 << " " << fn3 << endl;

    return 0;
}
