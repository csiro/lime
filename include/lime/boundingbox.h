#ifndef LIME_BOUNDINGBOX_H
#define LIME_BOUNDINGBOX_H

#include <cstring>
#include <iostream>

#include "lime/point.h"
#include "lime/displayable.h"

namespace lime {

    /** Defines a rectagle in terms of lower left (ll) and upper right (ur)
        locations. Can be modified to enclose a new location, and used to
        test a location for inclusion.
     */
    class BoundingBox : public Displayable
    {
    public:

        /** Default contructor. */
        BoundingBox();

        BoundingBox(const lime::Point* ll, const lime::Point* ur);


        virtual ~BoundingBox() {}

        void set (const lime::Point* ll, const lime::Point* ur);
        void enclose (const lime::Point* loc);

        bool contains(const lime::Point* loc) const;
        
        void display (std::ostream& os = std::cout) const override;

    protected:

        Point ll_;
        Point ur_;
    };
}

#endif
