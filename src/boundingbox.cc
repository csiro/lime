
#include "lime/boundingbox.h"

using namespace lime;

void
BoundingBox::enclose (const Point* loc)
{
    if (isEmpty_) {
        Box::set (loc, loc);
        isEmpty_ = false;
    }
    else {
        if (loc->x() < ll()->x())
            ll()->setX(loc->x());
        if (loc->y() < ll()->y())
            ll()->setY(loc->y());
        if (loc->x() > ur()->x())
            ur()->setX(loc->x());
        if (loc->y() > ur()->y())
            ur()->setY(loc->y());
    }
}

void
BoundingBox::enclose (const Box* box)
{
    enclose (box->ll());
    enclose (box->ur());
}

bool
BoundingBox::contains(const Point* loc) const
{
    if (isEmpty_)
        return false;
    return
        (loc->x() >= ll()->x()) &&
        (loc->y() >= ll()->y()) &&
        (loc->x() <= ur()->x()) &&
        (loc->y() <= ur()->y()
    );
}

void
BoundingBox::expand (double proportion)
{
    double wid = ur()->x() - ll()->x();
    double len = ur()->y() - ll()->y();

    ll()->set (
        ll()->x() - proportion / 2 * wid,
        ll()->y() - proportion / 2 * len
    );
    ur()->set (
        ur()->x() + proportion / 2 * wid,
        ur()->y() + proportion / 2 * len
    );
}
