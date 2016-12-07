#pragma once

/**
 *  Defines a dig distance or time that depends on the order of
 *  visiting requests.
 *  The index defines where in request and vehicle arrays
 *    this dig is stored
 */

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "lime/displayable.h"


namespace lime {

    class Point;

    class Dig : public Displayable
    {
    public:
        Dig(const char* filename, bool append = false);
        virtual ~Dig();

        void title (std::string title);
        void xLabel (std::string label);
        void yLabel (std::string label);
        void style (int style);
        void style (int colour, int mark);
        void nextStyle ();
        void nextDataset ();
        void mark (int m);
        void colourMark (int c, int m);
        void circle (double x, double y, int diam, bool filled = false);
        void circle (const lime::Point* p, int diam, bool filled = false);
        // set colour using red/blue/green - doubles in range 0 - 1
        void rgb (double r, double g, double b);
        // set colour using blue-red scale, 0 to max
        void colourScaleBR (double val, double max);
        // set colour using red-only scale, 0 to max
        void colourScaleR (double val, double max);
        void label (std::string label_);
        void labelPoint (double x, double y, std::string label);
        void labelPoint (const lime::Point* p, std::string label);
        void showMessage (std::string message, std::string message2 = "");
        void showMessage (std::string message, int i);
        void showMessage (std::string message, double d);
        void moveTo (double x, double y);
        void moveTo (const lime::Point* p);
        void drawTo (double x, double y);
        void drawTo (const lime::Point* p);
        void drawArrowedTo (double x, double y);
        void drawDistinctTo (double x, double y);
        void drawDistinctTo (const lime::Point* point);
        void draw (double x1, double y1, double x2, double y2);
        void box (double x1, double y1, double x2, double y2, int c);
        void xTic (double x, std::string label);
        void yTic (double y, std::string label);
        void wait ();
        void wipe ();
        void waitAndWipe ();
        void close ();
        std::ostream& outFile() {return out;}

        void display (std::ostream&) const override;

    protected:
        std::ofstream out;
        int currStyle;
    };

    typedef std::shared_ptr<Dig> DigPtr;

} //namespace

