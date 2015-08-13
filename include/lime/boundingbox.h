#ifndef LIME_BOUNDINGBOX_H
#define LIME_BOUNDINGBOX_H

/**
 *  Defines a rectagle, in terms of lower-left (ll) and upper-right (ur)
 *  locations
 */

#include <cstring>
#include <iostream>

#include "lime/point.h"

namespace lime {
    class BoundingBox
    {
    public:
        BoundingBox();
        BoundingBox(const lime::Point* ll, const lime::Point* ur);
        virtual ~BoundingBox() {}

        void set (const lime::Point* ll, const lime::Point* ur);
        void enclose (const lime::Point* loc);

        bool contains(const lime::Point* loc) const;

        void display (std::ostream&) const;

    protected:
        lime::Point ll_;
        lime::Point ur_;
    };

    std::ostream& operator<< (std::ostream&, const BoundingBox&);
}
#endif
