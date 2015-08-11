
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <2 Apr 2014 12:18:04>"

#include <assert.h>
#include <math.h>

#include "lime/line.h"

using namespace std;
using namespace lime;

void
Line::display (std::ostream& out) const
{
    out << p1_ << "-" << p2_;
}

ostream&
lime::operator<< (ostream& out, const Line& line)
{
    line.display (out);
    return out;
}

