
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
    double dX = this->getX() - x;
    double dY = this->getY() - y;
    return sqrt (dX * dX + dY * dY);
}

double
Point::distTo (const Point* other) const
{
    return distTo (other->getX(), other->getY());
}

void
Point::display (std::ostream& os) const
{
    os << "(" << x_ << "," << y_ << ")";
}

bool 
Point::operator<(const Point& point) const
{
    if (point.getX() < x_)
        return true;
    if (point.getX() == x_ && point.getY() < y_)
        return true;
    return false;
}
