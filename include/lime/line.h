#pragma once

#include <iostream>
#include <cmath>

#include "lime/point.h"
#include "lime/displayable.h"

namespace lime {
    
    class Line : public Displayable
    {
    public:
        Line() : p1_(), p2_() {}
        Line (const Point& p1, const Point& p2) : p1_(p1), p2_(p2) {}
        Line (const Line& other) : p1_(other.p1_), p2_(other.p2_) {}
        Line (double x1, double y1, double x2, double y2) :
            p1_(x1, y1),
            p2_(x2, y2)
        {}
        virtual ~Line() {}

        void setP1 (const Point& p1) {p1_ = p1;}
        void setP2 (const Point& p2) {p2_ = p2;}
        void set (const Point& p1, const Point& p2) {p1_ = p1; p2_ = p2;}
    
        const Point* p1() const {return &p1_;}
        const Point* p2() const {return &p2_;}
        double x1() const {return p1_.x();}
        double y1() const {return p1_.y();}
        double x2() const {return p2_.x();}
        double y2() const {return p2_.y();}

        double length () const {return p1_.distTo(&p2_);}

        double angle () const {
            return atan2 (p2_.y() - p1_.y(), p2_.x() - p1_.x());
        }

        void display (std::ostream& os = std::cout) const override
        {
            os << p1_ << "-" << p2_;
        }
    
    private:
        Point p1_;
        Point p2_;
    };
}

