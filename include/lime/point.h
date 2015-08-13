#ifndef LIME_POINT_H
#define LIME_POINT_H

#include <iostream>

namespace lime
{
    class Point
    {
    public:
        Point() : x_(0), y_(0) {}
        Point (double x, double y) : x_(x), y_(y) {}
        Point (const Point& other) : x_(other.x_), y_(other.y_) {}
        virtual ~Point() {}

        void setX (double x) {x_ = x;}
        void setY (double y) {y_ = y;}
        void set (double x, double y) {x_ = x; y_ = y;}

        double x() const {return x_;}
        double y() const {return y_;}

        double distTo (double x, double y) const;
        double distTo (const Point* other) const;

        Point* copy (const Point* other) {
            x_ = other->x_; y_ = other->y_; return this;
        }
        Point& operator=(const Point& other) {
            x_ = other.x_; y_ = other.y_; return *this;
        }
        bool  operator<(const Point& point) const;

        void display (std::ostream&) const;

    private:
        double x_;
        double y_;
    };

    std::ostream& operator<< (std::ostream&, const Point&);
}

#endif
