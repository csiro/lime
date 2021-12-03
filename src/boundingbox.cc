
/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../LICENCE.md
*/

#include "lime/boundingbox.h"

using namespace lime;

void
BoundingBox::enclose (double x, double y)
{
    if (isEmpty_) {
        Point ll (x, y);
         Box::set (&ll, &ll);
        isEmpty_ = false;
    }
    else {
        if (x < ll()->x())
            ll()->setX(x);
        if (y < ll()->y())
            ll()->setY(y);
        if (x > ur()->x())
            ur()->setX(x);
        if (y > ur()->y())
            ur()->setY(y);
    }
}

void
BoundingBox::enclose (const Point* loc)
{
    enclose (loc->x(), loc->y());
}

void
BoundingBox::enclose (const Box* box)
{
    enclose (box->ll());
    enclose (box->ur());
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

