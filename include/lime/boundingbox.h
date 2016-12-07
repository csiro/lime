#pragma once

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
        BoundingBox() :
            ll_(0, 0),
            ur_(0, 0)
        { }

        /** Constructor. 
            @param ll lower-left corner
            @param ur upper-right corner
         */
        BoundingBox(const lime::Point* ll, const lime::Point* ur)  :
            ll_(*ll),
            ur_(*ur)
        { }

        /** (Virtual) destructor. */
        virtual ~BoundingBox() { }

        /** Set both corners at the same time. 
            @param ll lower-left corner
            @param ur upper-right corner
         */
        void set (const lime::Point* ll, const lime::Point* ur)
        {
            ll_ = *ll;
            ur_ = *ur;
        }
        
        /** Add a point to the bounding box, possibly enlarging the box to
            accomodate the new point.
            @param loc new Point to add
         */
        void enclose (const lime::Point* loc);

        /** Check whether a point is enclosed in the bounding box.
            @param loc Point to check
         */
        bool contains(const lime::Point* loc) const;
        
        /** @copydoc Displayable::display(std::ostream&) */
        void display (std::ostream& os = std::cout) const override
        {
            os << "[" << ll_ << " - " << ur_ << "]";
        }

    protected:

        /** Lower-left corner. */
        Point ll_;
            
        /** Upper-right corner. */
        Point ur_;
    };
}

