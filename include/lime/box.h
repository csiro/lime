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

    class Dig;
    
    class Box : public Displayable
    {
    public:

        /** Default contructor. */
        Box() :
            ll_(0, 0),
            ur_(0, 0)
        { }
        
        /** Constructor. 
            @param ll lower-left corner
            @param ur upper-right corner
         */
        Box(const lime::Point* ll, const lime::Point* ur)  :
            ll_(*ll),
            ur_(*ur)
        { }

        /** Constructor. 
            @param ll(x,y) lower-left corner x and y
            @param ur(x,y) upper-right corner x and y
         */
        Box(double llx, double lly, double urx, double ury)  :
            ll_(llx, lly),
            ur_(urx, ury)
        { }
        
        Box(const Box& other)  :
            ll_(*other.ll()),
            ur_(*other.ur())
        { }

        Box& operator=(const Box& other) {
            ll_ = other.ll_;
            ur_ = other.ur_;
            return *this;
        }
        
        Point* ll() {return &ll_;}
        const Point* ll() const {return &ll_;}
        double llx() const {return ll_.x();}
        double lly() const {return ll_.y();}
        Point* ur() {return &ur_;}
        const Point* ur() const {return &ur_;}
        double urx() const {return ur_.x();}
        double ury() const {return ur_.y();}

        double width() const {return ur_.x() - ll_.x();}
        double height() const {return ur_.y() - ll_.y();}

        bool overlaps (const Box* other) const;
        bool contains (const Point* point) const {
            return
                llx() <= point->x() && point->x() <= urx() &&
                lly() <= point->y() && point->y() <= ury();
        }

        /** Set both corners at the same time. 
            @param ll lower-left corner
            @param ur upper-right corner
         */
        void set (const lime::Point* ll, const lime::Point* ur)
        {
            ll_ = *ll;
            ur_ = *ur;
        }
        void set (double llx, double lly, double urx, double ury)
        {
            ll_.set (llx, lly);
            ur_.set (urx, ury);
        }
        
        void centre (Point& pt)
        {
            double wid = (ur_.x() - ll_.x()) / 2.0;
            double len = (ur_.y() - ll_.y()) / 2.0;
            pt.set (ll_.x() + wid, ll_.y() + len);
        }
        
        /** Translate by deltax and deltay */
        void translate (double deltaX, double deltaY)
        {
            ll_.translate (deltaX, deltaY);
            ur_.translate (deltaX, deltaY);
        }

        void draw (Dig* dig, double xOffset = 0.0, double yOffset = 0.0);
        
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

