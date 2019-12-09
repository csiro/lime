

#include <iostream>
#include <sstream>
#include <cstring>

#include "lime/hilbert.h"

using namespace lime;
using namespace std;


void
Usage (const char* cmd, const char* message1 = 0, const char* message2 = 0)
{
    if (message1)
        cerr << message1;
    if (message2)
        cerr << " " << message2;
    if (message1 || message2)
        cerr << endl;
    cerr << "Usage: " << endl;
    cerr << "    " << cmd << " [-n #]" << endl;
    cerr << " or " << cmd << " [-n #] <x-max> <y-max> < filename" << endl;
    cerr << R"(
Description
    With no args:
	Outputs coords describing the Hilbert curve.
    With args:
	Reads lines from file, and converts coords into positions
	on the Hilbert curve. x y must be first fields of line.
	Hilbert fills space (0,0) to (x-max,y-max)
    Switches:
	-n: Number of bits in rep [14] - max 14
)";
    cerr << "This build " << __DATE__ << " " << __TIME__ << endl;
    exit (1);
}

int main (int argc, char* argv[])
{
    int upto = 1;
    int nbits = 14;
    double width = -1;
    double height = -1;
    
    for (upto = 1; upto < argc; upto++) {
        if (*argv[upto] == '-') {
            if (!strcmp (argv[upto], "-n") && upto < argc-1) {
                nbits = atoi(argv[++upto]);
            }
            else
                Usage (argv[0], "Unrecognised option: ", argv[upto]);
        }
        else if (width < 0)
            width = atof (argv[upto]);
        else if (height < 0)
            height = atof (argv[upto]);
        else
            Usage (argv[0], "Too many args: ", argv[upto]);
    }

    if (height < 0) {
        Hilbert hilbert (nbits, 1000, 1000);
        
        int maxIndex = (1 << nbits);
        cerr << "maxIndex is " << maxIndex << " nbits " << nbits << endl;
    
        for (int i = 0; i < maxIndex; i++) {
            double pos = (double)i/maxIndex;
            double x, y;
            hilbert.posToCoord (pos, x, y);
            cout << x << " " << y << endl;
        }
    }
    else {
        Hilbert hilbert (nbits, width, height);
    
        string line;
        while (getline(std::cin, line)) {
            stringstream strm (line);
            double x, y;
            strm >> x >> y;
            if (!strm.fail()) 
                cout << hilbert.coordToPos (x, y) << " " << line << endl;
        }
    }
    
    return 0;
}


    
