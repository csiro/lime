
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
        cout << "Type? ";
        string type;
        getline(cin, type);
        cout << ">" << line << "<>" << delim << "<" << endl;
        split.split(line, delim.c_str(), "#");
        cout << "Found " << split.numTokens() << " tokens" << endl;
        for (size_t k = 0; k < split.numTokens(); k++) {
            cout << "Tok " << k << ": ";
            bool error = false;
            if (type.compare("i") == 0) 
                cout << split.token(k) << " " << split.nextInt(error);
            else if (type.compare("d") == 0) 
                cout << split.token(k) << " " << split.nextDouble(error);
            else if (type.compare("b") == 0) 
                cout << split.token(k) << " " << split.nextBool(error);
            else if (type.compare("t") == 0) 
                cout << split.token(k) << " " << split.nextTime(error);
            else 
                cout << split.token(k) << " " << split.next(error);
            cout << " err " << error << endl;
        }
        cout << "String? ";
    }
}
