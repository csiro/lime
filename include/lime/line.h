#pragma once

#include <iostream>

#include "lime/point.h"
#include "lime/displayable.h"

namespace lime {
    
    class Line : public Displayable
    {
    public:
        Line() : p1_(), p2_() {}
        Line (const Point& p1, const Point& p2) : p1_(p1), p2_(p2) {}
        Line (const Line& other) : p1_(other.p1_), p2_(other.p2_) {}
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

        void display (std::ostream& os = std::cout) const override
        {
            os << p1_ << "-" << p2_;
        }
    
    private:
        Point p1_;
        Point p2_;
    };
}

