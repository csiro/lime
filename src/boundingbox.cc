
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <10 Jun 2015 23:51:47>"

/** Implement the "boundingBox" methods */

#include <cstdio>
#include <iostream>
#include <sstream>

#include "lime/boundingbox.h"

using namespace std;
using namespace lime;

BoundingBox::BoundingBox() :
    ll_(0, 0),
    ur_(0, 0)
{
}

BoundingBox::BoundingBox(const Point* ll, const Point* ur) :
    ll_(*ll),
    ur_(*ur)
{
}

void
BoundingBox::set(const Point* ll, const Point* ur) 
{
    ll_ = *ll;
    ur_ = *ur;
}

void
BoundingBox::enclose (const Point* loc)
{
    if (loc->x < ll_.x)
        ll_.x = loc->x;
    if (loc->y < ll_.y)
        ll_.y = loc->y;
    if (loc->x > ur_.x)
        ur_.x = loc->x;
    if (loc->y > ur_.y)
        ur_.y = loc->y;
}

bool
BoundingBox::contains(const Point* loc) const
{
    return
        (loc->x >= ll_.x) &&
        (loc->y >= ll_.y) &&
        (loc->x <= ur_.x) &&
        (loc->y <= ur_.y);
}
    

void
BoundingBox::display (ostream& out) const
{
    out << "[" << ll_ << " - " << ur_ << "]";
}

// ------------------------

ostream&
operator<< (ostream& out, const BoundingBox& box)
{
    box.display (out);
    return out;
}
