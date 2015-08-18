
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <10 Jun 2015 23:51:47>"

#include "lime/boundingbox.h"

using namespace lime;

void
BoundingBox::enclose (const Point* loc)
{
    if (loc->getX() < ll_.getX())
        ll_.setX(loc->getX());
    if (loc->getY() < ll_.getY())
        ll_.setY(loc->getY());
    if (loc->getX() > ur_.getX())
        ur_.setX(loc->getX());
    if (loc->getY() > ur_.getY())
        ur_.setY(loc->getY());
}

bool
BoundingBox::contains(const Point* loc) const
{
    return
        (loc->getX() >= ll_.getX()) &&
        (loc->getY() >= ll_.getY()) &&
        (loc->getX() <= ur_.getX()) &&
        (loc->getY() <= ur_.getY()
    );
}
