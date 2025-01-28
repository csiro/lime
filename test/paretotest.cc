
#include <iostream>
#include <sstream>

#include "lime/pareto.h"

using namespace std;
using namespace lime;

string vec_to_str (vector<double> vec)
{
    stringstream str;
    for (auto val : vec) {
        str << " " << (int) val;
    }
    return str.str();
}

vector<double> tovec (int x, int y)
{
    vector<double> ret ({(double)x, (double)y});
    return ret;
}

void show (ParetoFront<string>& pareto)
{
    cout << "Front is " << endl;
    for (size_t k = 0; k < pareto.size(); k++) {
        cout << "  " << pareto.solution(k) << endl;
    }

}

int
main ()
{
    Debug::setFilename ("debug.out");
    Debug::setKey ("P");
    
    ParetoFront<string> pareto;

    list<string> names;

    vector<double> vec = tovec (10, 20);
    string name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (11, 21);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (5, 21);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (4, 21);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (7, 22);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (7, 20);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (7, 19);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (8, 19);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (9, 20);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (5, 20);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (8, 16);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (9, 9);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (14, 14);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    vec = tovec (6, 17);
    name = vec_to_str (vec);
    names.push_back (name);
    cout << "Add " << name << " " << pareto.add (vec, name) << endl;
    show (pareto);

    ofstream dig ("pareto.dig");
    dig << "S 1" << endl;
    for (auto str : names)
        dig << "M " << str << endl;

    dig << endl;
    dig << "S 2" << endl;
    cout << "Front is " << endl;
    for (size_t k = 0; k < pareto.size(); k++) {
        cout << pareto.solution(k) << endl;
        dig << "M " << pareto.solution(k) << endl;
    }
    cout << "Check out dig with" << endl;
    cout << "dig pareto.dig &" << endl;
}
