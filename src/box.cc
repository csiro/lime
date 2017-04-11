
#include "lime/box.h"
#include "lime/dig.h"

using namespace lime;

void
Box::draw (Dig* dig, double xOffset, double yOffset)
{
    dig->moveTo (ll_.x() + xOffset, ll_.y() + yOffset);
    dig->drawTo (ll_.x() + xOffset, ur_.y() + yOffset);
    dig->drawTo (ur_.x() + xOffset, ur_.y() + yOffset);
    dig->drawTo (ur_.x() + xOffset, ll_.y() + yOffset);
    dig->drawTo (ll_.x() + xOffset, ll_.y() + yOffset);
}
