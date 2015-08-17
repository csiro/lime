#ifndef LIME_POINT_H
#define LIME_POINT_H

#include <iostream>

namespace lime
{
    /** A class representing a 2-dimensional point. */
    struct Point
    {
        /** Default constructor.
            @remarks initialises the point at the origin (0,0).
         */
        Point() : x(0), y(0) { }
        
        /** Constructor.
            @param x the x-coordinate
            @param y the y-coordinate
         */
        Point (double x, double y) : x(x), y(y) { }
        
        /** Resets both coordinates at once. */
        void set(double x, double y)
        {
            this->x = x;
            this->y = y;
        }
        
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

        /** Display method.
            @param os the stream onto which this object must be "displayed".
         */
        void display (std::ostream&) const;

        /** The x-coordinate. */
        double x;
        
        /** The y-coordinate. */
        double y;
    };

    /** Output operator. 
        @param os stream to write to
        @param o object to print
     */
    std::ostream& operator<< (std::ostream& os, const Point& o);
}

#endif
