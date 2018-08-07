
#include "lime/box.h"
#include "lime/dig.h"

using namespace lime;

bool
Box::overlaps(const Box* other) const
{
    // Not if one rectangle is on left side of other
    return
        llx() < other->urx() &&
        urx() > other->llx() &&
        ury() > other->lly() &&
        lly() < other->ury();
 
    return true;
}

void
Box::draw (Dig* dig, double xOffset, double yOffset)
{
    dig->moveTo (ll_.x() + xOffset, ll_.y() + yOffset);
    dig->drawTo (ll_.x() + xOffset, ur_.y() + yOffset);
    dig->drawTo (ur_.x() + xOffset, ur_.y() + yOffset);
    dig->drawTo (ur_.x() + xOffset, ll_.y() + yOffset);
    dig->drawTo (ll_.x() + xOffset, ll_.y() + yOffset);
}
