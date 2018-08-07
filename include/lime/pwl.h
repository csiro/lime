#pragma once

#include <iostream>
#include <list>

#include "lime/displayable.h"

namespace lime
{
    /** A class representing a piece-wise linear function.
        The function can be discontinuous, in which case the left-most
        value will be used at the discontinuity
     */
    class PiecewiseLinear : public Displayable
    {
    public:
        
        /** Default constructor.
            @remarks initialises the point at the origin (0,0).
         */
        PiecewiseLinear() :
            entries_()
        {}

        void add (double x, double y) {entries_.push_back (Entry(x, y));}

        double valueAt (double x) const;
        
        /** Display method.
            @param os the stream onto which this object must be "displayed".
         */
        void display (std::ostream& os = std::cout) const override;
        void displaySimple (std::ostream& os = std::cout) const;

    private:

        struct Entry
        {
            Entry (double x_, double y_) :
                x(x_), y(y_) {}

            double x;
            double y;
        };
        struct EntryLess
        {
            bool operator()(const Entry& a, const Entry& b) const {
                if (a.x != b.x)
                    return a.x < b.x;
                return a.y < b.y;
            }
        };
            
        std::list<Entry> entries_;
    };
    
    std::ostream& operator<< (std::ostream&, const PiecewiseLinear&);
}

