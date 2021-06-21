
#include <vector>

#include "lime/randgen.h"
#include "lime/strutil.h"

using namespace std;
using namespace lime;

std::shared_ptr<RandGen>
RandGen::makeRandGen (string fullName, int seed)
{
    string name;
    vector<double> args;
    auto brace = fullName.find("(");
    if (brace == string::npos) {
        name = fullName;
    }
    else {
        name = fullName.substr(0, brace);
        auto lastPos = brace + 1;
        auto comma = fullName.find_first_of(",)", lastPos);
        while (comma != string::npos) {
            double d = stod (fullName.substr(lastPos, comma - lastPos));
            args.push_back(d);
            lastPos = comma + 1;
            comma = fullName.find_first_of(",)", lastPos);
        }
    }
    name = toLower (name);
    if (name.compare ("constant") == 0) {
        if (args.size() < 1)
            return nullptr;
        return std::make_shared<RandConstant> (args[0], seed);
    }
    else if (name.compare ("uniform01") == 0) {
        return std::make_shared<RandUniform01> (seed);
    }
    else if (name.compare ("uniform") == 0) {
        if (args.size() < 2)
            return nullptr;
        return
            std::make_shared<RandUniform> (args[0], args[1], seed);
    }
    else if (name.compare ("uniform0n-1") == 0) {
        if (args.size() < 1)
            return nullptr;
        return std::make_shared<RandUniform0n_1> ((int)args[0], seed);
    }
    else if (name.compare ("normal01") == 0) {
        return std::make_shared<RandNormal01> (seed);
    }
    else if (name.compare ("normal") == 0) {
        if (args.size() < 2)
            return nullptr;
        return std::make_shared<RandNormal> (args[0], args[1], seed);
    }
    else if (name.compare ("truncnormal") == 0) {
        if (args.size() < 4)
            return nullptr;
        return
            std::make_shared<RandTruncNormal> (
                args[0], args[1], args[2], args[3], seed
            );
    }
    else if (name.compare ("lognormal") == 0) {
        if (args.size() < 2)
            return nullptr;
        return
            std::make_shared<RandLogNormal> (

                args[0], args[1], seed
            );
    }
    else if (name.compare ("stdexp") == 0) {
        return
            std::make_shared<RandStdExponential> (seed);
    }
    else if (name.compare ("exp") == 0) {
        if (args.size() < 1)
            return nullptr;
        return std::make_shared<RandExponential> (args[0], seed);
    }
    else if (name.length() > 0 && (isdigit(name[0]) || name[0] == '-' || name[0] == '.')) {
        // It's a number - use it as a constant 
        double c = stod (name);
        return std::make_shared<RandConstant> (c, seed);
    }
    else
        return nullptr;
}
