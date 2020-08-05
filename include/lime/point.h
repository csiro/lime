#pragma once

#include <iostream>

#include "lime/numutil.h"
#include "lime/displayable.h"

namespace lime
{
    /** A class representing a 2 or 3-dimensional point. */
    class Point : public Displayable
    {
    public:
        
        /** Default constructor.
            @remarks initialises the point at the origin (0,0).
         */
        Point() : x_(0), y_(0), z_(0) { }
        
        /** Constructor.
            @param x the x-coordinate
            @param y the y-coordinate
            @param z the z-coordinate
         */
        Point (double x, double y, double z = 0.0) : x_(x), y_(y), z_(z) {}
        
        /** Copy constructor.
            @param other the point to be copied
         */
        Point (const Point& other) : x_(other.x_), y_(other.y_), z_(other.z_) {}
        
        /** Resets both coordinates at once. */
        void set(double x, double y, double z = 0.0)
        {
            x_ = x;
            y_ = y;
            z_ = z;
        }
        
        /** Resets both coordinates at once. */
        void set(const Point* other)
        {
            x_ = other->x_;
            y_ = other->y_;
            z_ = other->z_;
        }
        
        /** Traslate by given delta . */
        void translate (double deltaX, double deltaY, double deltaZ = 0.0)
        {
            x_ += deltaX;
            y_ += deltaY;
            z_ += deltaZ;
        }
        
        /** Read x. */
        const double x() const { return x_; }
        
        /** Read y. */
        const double y() const { return y_; }
        
        /** Read z. */
        const double z() const { return z_; }
        
        /** Update x.
            @param x new value of x
         */
        void setX(const double x) { x_ = x; }
        
        /** Update y.
            @param y new value of y
         */
        void setY(const double y) { y_ = y; }
        
        /** Update z.
            @param z new value of z
         */
        void setZ(const double z) { z_ = z; }
        
        /** Computes the distance from a set of coordinates.
            @param x the x-coordinate
            @param y the y-coordinate
            @return the distance from the given set of coordinates
         */
        double distTo (double x, double y, double z = 0.0) const;
        
        /** Computes the distance from a Point.
            @param point the Point to compute the distance from
            @return the distance from the Point
         */
        double distTo (const Point* other) const;

        bool equals (double x, double y) const {
            return limeDblEqual (x, x_) && limeDblEqual (y, y_);
        }
        bool equals (const Point* pt) const {
            return equals (pt->x(), pt->y());
        }

        /** Clones another Point, returns pointer to self.
            @param other Point to copy.
            @return pointer to self
         */
        Point* copy (const Point* other)
        {
            *this = *other; // copy through implicit copy assignment
            return this;
        }
        
        /** Checks if the Point is lexicographically smaller than another Point.
            @param point the point to check
         */
        bool  operator<(const Point& point) const;

        Point& operator=(const Point& other) {
            x_ = other.x_;
            y_ = other.y_;
            z_ = other.z_;
            return *this;
        }
        
        /** Display method.
            @param os the stream onto which this object must be "displayed".
         */
        void display (std::ostream& os = std::cout) const override;

    private:
        
        /** The x-coordinate. */
        double x_;
        
        /** The y-coordinate. */
        double y_;
        
        /** The z-coordinate. */
        double z_;
    };
    
    std::ostream& operator<< (std::ostream&, const Point&);
}

