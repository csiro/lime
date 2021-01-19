
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "lime/opts.h"
#include "lime/config.h"

using namespace std;
using namespace lime;

int
main(int argc, const char* argv[])
{
    string descr = R"(A description across
multiple lines.)";

    Config config;
    config.addItem ("item", "value");
    
    Opts opts (descr, __DATE__, __TIME__);

    int n = 1;
    bool b = false;
    double d = 1.2345;

    string fn1 = "";
    string fn2 = "blah";

    opts.add_opt ("-n", &n, "Number of something");
    opts.add_opt ("-b", &b, "Bool something");
    opts.add_opt ("-c", &config, "Config filename");
    opts.add_opt ("-d", &d, "Double something");

    opts.add_arg ("file1", &fn1, "First fn");
    opts.add_optional_arg ("file2", &fn2, "Second fn");

    if (!opts.process (argc, argv, &config))
        exit(1);

    cout << "  n: " << n << endl;
    cout << "  b: " << b << endl;
    cout << "  d: " << d << endl;
    cout << "fn1: " << fn1 << endl;
    cout << "fn2: " << fn2 << endl;
    cout << "Config: " << config << endl;
    
    return 0;
}
