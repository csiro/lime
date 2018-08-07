#include <cassert>
#include <cmath>

#include "lime/pwl.h"
#include "lime/numutil.h"

using namespace std;
using namespace lime;

double
PiecewiseLinear::valueAt (double x) const
{
    assert (entries_.size() > 0);

    auto iter = entries_.begin();
    double prevX = (*iter).x;
    double prevY = (*iter).y;
    if (x < prevX)
        return prevY;
    ++iter;
    while (iter != entries_.end()) {
        auto currX = (*iter).x;
        auto currY = (*iter).y;
        if (x <= currX) {
            assert (currX != prevX);
            return prevY + (x - prevX) * (currY - prevY) / (currX - prevX);
        }
        prevX = currX;
        prevY = currY;
        ++iter;
    }
    return prevY;
}


void
PiecewiseLinear::displaySimple (std::ostream& out) const
{
    for (auto e : entries_) {
        out << "  " << e.x << " " << e.y;
    }
}

void
PiecewiseLinear::display (std::ostream& out) const
{
    out << "{";
    for (auto e : entries_) {
        out << "[" << e.x << "," << e.y << "]";
    }
    out << "}";
}

std::ostream&
lime::operator<< (ostream& out, const PiecewiseLinear& pwl)
{
    pwl.display (out);
    return out;
}
