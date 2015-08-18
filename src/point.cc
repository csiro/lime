
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
    double dX = this->x - x;
    double dY = this->y - y;
    return sqrt (dX * dX + dY * dY);
}

double
Point::distTo (const Point* other) const
{
    return distTo (other->x, other->y);
}

void
Point::display (std::ostream& os) const
{
    os << "(" << x << "," << y << ")";
}

bool 
Point::operator<(const Point& point) const
{
    if (point.x < x) {
        return true;
    }
    else if (point.x == x) {
        if (point.y < y) {
            return true;
        }
    }
    return false;
}
