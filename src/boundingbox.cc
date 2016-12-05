#include "lime/boundingbox.h"

using namespace lime;

void
BoundingBox::enclose (const Point* loc)
{
    if (loc->x() < ll_.y())
        ll_.setX(loc->x());
    if (loc->y() < ll_.y())
        ll_.setY(loc->y());
    if (loc->x() > ur_.x())
        ur_.setX(loc->x());
    if (loc->y() > ur_.y())
        ur_.setY(loc->y());
}

bool
BoundingBox::contains(const Point* loc) const
{
    return
        (loc->x() >= ll_.x()) &&
        (loc->y() >= ll_.y()) &&
        (loc->x() <= ur_.x()) &&
        (loc->y() <= ur_.y()
    );
}
