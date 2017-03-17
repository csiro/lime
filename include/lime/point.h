#pragma once

#include <iostream>

#include "lime/displayable.h"

namespace lime
{
    /** A class representing a 2-dimensional point. */
    class Point : public Displayable
    {
    public:
        
        /** Default constructor.
            @remarks initialises the point at the origin (0,0).
         */
        Point() : x_(0), y_(0) { }
        
        /** Constructor.
            @param x the x-coordinate
            @param y the y-coordinate
         */
        Point (double x, double y) : x_(x), y_(y) { }
        
        /** Copy constructor.
            @param other the point to be copied
         */
        Point (const Point& other) : x_(other.x_), y_(other.y_) { }
        
        /** Resets both coordinates at once. */
        void set(double x, double y)
        {
            x_ = x;
            y_ = y;
        }
        
        /** Traslate by given delta . */
        void translate (double deltaX, double deltaY)
        {
            x_ += deltaX;
            y_ += deltaY;
        }
        
        /** Read x. */
        const double& x() const { return x_; }
        
        /** Read y. */
        const double& y() const { return y_; }
        
        /** Update x.
            @param x new value of x
         */
        void setX(const double& x) { x_ = x; }
        
        /** Update y.
            @param y new value of y
         */
        void setY(const double& y) { y_ = y; }
        
        /** Computes the distance from a set of coordinates.
            @param x the x-coordinate
            @param y the y-coordinate
            @return the distance from the given set of coordinates
         */
        double distTo (double x, double y) const;
        
        /** Computes the distance from a Point.
            @param point the Point to compute the distance from
            @return the distance from the Point
         */
        double distTo (const Point* other) const;

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

        const Point& operator=(const Point& other) {
            x_ = other.x_;
            y_ = other.y_;
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
    };
    
    std::ostream& operator<< (std::ostream&, const Point&);
}

