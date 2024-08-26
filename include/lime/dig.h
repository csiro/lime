#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


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
    class Line;
    class Box;

    class Dig : public Displayable
    {
    public:
        enum Markers {
            NO_MARK=0, CIRCLE, STAR, SQUARE, CROSS, DOWN_TRIANGLE, 
            UP_TRIANGLE, FILLED_SQUARE, FILLED_CIRCLE, PLUS, VBAR, HBAR,
            NUM_MARKERS
        };
        enum StyleColours {
            BLACK =0, BLUE, RED, DARK_GREEN, CYAN, SIENNA, MAGENTA,
            CORAL, ORANGE, PINK, CADET_BLUE, NUM_COLOURS
        };
        enum StyleStroke {
            THIN, DASHED, THICK
        };

        Dig(const char* filename, bool append = false);
        Dig(const std::string filename, bool append = false);
        virtual ~Dig();

        void title (const char* title);
        void title (std::string title);
        void latLong ();
        void xLabel (const char* label);
        void xLabel (std::string label);
        void yLabel (const char* label);
        void yLabel (std::string label);
        void style (int style);
        void style (int colour, int mark);
        void style (int colour, int mark, int stroke);
        void nextStyle ();
        void nextDataset ();
        void mark (int m);
        void colourMark (int c, int m);
        void circle (double x, double y, int diam, bool filled = false);
        void circle (const lime::Point* p, int diam, bool filled = false);
        void scaledCircle (
            double x, double y, 
            double val, double minVal, double maxVal,
            int minSizePixels, int maxSizePixels,
            bool filled = false
        );
        // set colour using red/blue/green - doubles in range 0 - 1
        void rgb (double r, double g, double b);
        // set colour using blue-red scale, 0 to max
        void colourScaleBR (double val, double max);
        // set colour using red-only scale, 0 to max
        void colourScaleR (double val, double max);
        // set colour using grey scale (white to black), 0 to max
        void colourScaleGrey (double val, double max);
        void label (const char* label_, bool silent = false);
        void label (std::string label_, bool silent = false);
        // Allow legend as a synonym of label
        void legend (const char* label_) {label (label_);}
        void legend (std::string label_) {label (label_);}
        void labelPoint (double x, double y, const char* label);
        void labelPoint (double x, double y, std::string label);
        void labelPoint (const lime::Point* p, const char* label);
        void labelPoint (const lime::Point* p, std::string label);
        void showMessage (const char* message, const char* message2 = "");
        void showMessage (std::string message);
        void showMessage (const char* message, int i);
        void showMessage (const char* message, double d);
        void moveTo (double x, double y);
        void moveTo (const lime::Point* p);
        void drawTo (double x, double y);
        void drawTo (const lime::Point* p);
        void drawArrowedTo (double x, double y);
        void drawArrowedTo (const lime::Point* point);
        void drawDistinctTo (double x, double y);
        void drawDistinctTo (const lime::Point* point);
        void drawBezierTo (double x, double y);
        void drawBezierTo (const lime::Point* point);
        void drawCurveTo (double x, double y, int bend = 0);
        void drawCurveTo (const lime::Point* point, int bend = 0);
        void draw (double x1, double y1, double x2, double y2);
        void draw (const lime::Point* a, const lime::Point* b);
        void draw (const lime::Line* line);
        void box (double x1, double y1, double x2, double y2, int c);
        void box (const lime::Box* box, int c);
        // Note: Scale is in range [0,1] - blue - yellow - red
        void boxScale (double x, double y, double wid, double hgt, double scale);
        void boxOutline (const lime::Box* box);
        void fillPoly();
        void xTic (double x, const char* label);
        void xTic (double x, std::string label);
        void yTic (double y, const char* label);
        void yTic (double y, std::string label);
        void wait ();
        void wipe ();
        void waitAndWipe ();
        void close ();
        std::ostream& outFile() {return out;}

        // Precision of output
        void setPrecision (int prec_) {prec = prec_;}

        // Constants from the Dig program
        int numStdColours() const {return 11;}
        int numStdMarks() const {return 10;}
        int numStdStrokes() const {return 3;}

        void display (std::ostream&) const override;

    protected:
        std::ofstream out;
        int currStyle;
        int prec;
    };

    typedef std::shared_ptr<Dig> DigPtr;
    typedef Dig* DigRPtr;

} //namespace

