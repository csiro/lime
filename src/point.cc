#include <cassert>
#include <cmath>

#include "lime/point.h"

using namespace std;
using namespace lime;

double
Point::distTo (double x, double y, double z) const
{
    double dX = this->x() - x;
    double dY = this->y() - y;
    double dZ = this->z() - z;
    return sqrt (dX * dX + dY * dY + dZ * dZ);
}

double
Point::distTo (const Point* other) const
{
    return distTo (other->x(), other->y(), other->z());
}

void
Point::display (std::ostream& os) const
{
    os << "(" << x_ << "," << y_;
    if (z_ != 0.0)
        os << "," << z_;
    os << ")";
}

bool 
Point::operator<(const Point& other) const
{
    if (other.x() < x_)
        return true;
    if (other.x() == x_ && other.y() < y_)
        return true;
    if (other.x() == x_ && other.y() == y_ && other.z() < z_)
        return true;
    return false;
}

