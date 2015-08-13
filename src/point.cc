
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <3 Jun 2015 17:49:12>"

#include <cassert>
#include <cmath>

#include "lime/point.h"

using namespace std;
using namespace lime;

double
Point::distTo (double x, double y) const
{
    double dX = x_ - x;
    double dY = y_ - y;
    return sqrt (dX * dX + dY * dY);
}

double
Point::distTo (const Point* other) const
{
    return distTo (other->x(), other->y());
}

void
Point::display (std::ostream& out) const
{
    out << "(" << x_ << "," << y_ << ")";
}

bool 
Point::operator<(const Point& point) const
{
    if (point.x_ < x_) {
        return true;
    }
    else if (point.x_ == x_) {
        if (point.y_ < y_) {
            return true;
        }
    }
    return false;
}

ostream&
lime::operator<< (ostream& out, const Point& point)
{
    point.display (out);
    return out;
}

