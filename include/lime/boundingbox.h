#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


#include <cstring>
#include <iostream>

#include "lime/point.h"
#include "lime/box.h"

namespace lime {

    /** Defines a rectagle in terms of lower left (ll) and upper right (ur)
        locations. Can be modified to enclose a new location, and used to
        test a location for inclusion.
     */
    class BoundingBox : public Box
    {
    public:

        /** Default contructor. */
        BoundingBox() :
            Box(),
            isEmpty_(true)
        { }
        
        /** Constructor. 
            @param ll lower-left corner
            @param ur upper-right corner
         */
        BoundingBox(const lime::Point* ll, const lime::Point* ur)  :
            Box (ll, ur),
            isEmpty_(false)
        { }

        /** Constructor. 
            @param ll(x,y) lower-left corner x and y
            @param ur(x,y) upper-right corner x and y
         */
        BoundingBox(double llx, double lly, double urx, double ury)  :
            Box (llx, lly, urx, ury),
            isEmpty_(false)
        { }

        bool isEmpty() const {return isEmpty_;}
        
        /** Set both corners at the same time. 
            @param ll lower-left corner
            @param ur upper-right corner
         */
        void set (const lime::Point* ll, const lime::Point* ur)
        {
            Box::set (ll, ur);
            isEmpty_ = false;
        }
        void set (double ll_x, double ll_y, double ur_x, double ur_y)
        {
            Box::set (ll_x, ll_y, ur_x, ur_y);
            isEmpty_ = false;
        }

        /** Add a point to the bounding box, possibly enlarging the box to
            accomodate the new point.
            @param loc new Point to add
         */
        void enclose (double x, double y);
        void enclose (const lime::Point* loc);
        void enclose (const lime::Box* box);

        /** Expand the box by some proportion.
            porportion 1.1 is a 10% expansion, 1.0 is the same box
         */
        void expand (double proportion);
        
        /** Check whether a point is enclosed in the box.
            @param loc Point to check
         */
        bool contains(const lime::Point* loc) const;

        /** @copydoc Displayable::display(std::ostream&) */
        void display (std::ostream& os = std::cout) const override
        {
            if (isEmpty_)
                os << "[empty]";
            else
                os << "[" << ll_ << " - " << ur_ << "]";
        }

    protected:
        /** Have I been initialised? */
        bool isEmpty_;
    };
}

