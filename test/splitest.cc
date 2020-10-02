
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "lime/splitter.h"

using namespace std;
using namespace lime;

main()
{
    Splitter split;

    cout << "String? ";
    for (
        string line;
        getline(cin, line);
    ) {
        cout << "Delim? ";
        string delim;
        getline(cin, delim);
        cout << ">" << line << "<>" << delim << "<" << endl;
        split.split(line, delim.c_str(), "#");
        cout << "Found " << split.numTokens() << " tokens" << endl;
        for (size_t k = 0; k < split.numTokens(); k++) {
            cout << "Tok " << k << ": >" << split.token(k) << "<" << endl;
        }
        cout << "String? ";
    }
}
