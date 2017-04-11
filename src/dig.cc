/** Write a file to display stuff using the "Dig" program */

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#include "lime/dig.h"
#include "lime/point.h"

using namespace std;
using namespace lime;

Dig::Dig (const char* filename, bool append) :
    out (filename, ofstream::out | (append ? ofstream::app : ofstream::trunc)),
    currStyle(0)
{
}

Dig::Dig (string filename, bool append) :
    out (filename, ofstream::out | (append ? ofstream::app : ofstream::trunc)),
    currStyle(0)
{
}

Dig::~Dig ()
{
    out.close();
}

void
Dig::title (const char* title)
{
    out << "H \"" << title << "\"" << endl;
    out << "S 1" << endl;
    currStyle = 1;
}

void
Dig::title (string title)
{
    out << "H \"" << title << "\"" << endl;
    out << "S 1" << endl;
    currStyle = 1;
}

void
Dig::xLabel (const char* label)
{
    out << "X \"" << label << "\"" << endl;
}

void
Dig::xLabel (string label)
{
    out << "X \"" << label << "\"" << endl;
}

void
Dig::yLabel (const char* label)
{
    out << "Y \"" << label << "\"" << endl;
}

void
Dig::yLabel (string label)
{
    out << "Y \"" << label << "\"" << endl;
}

void
Dig::label (const char* label_)
{
    out << "L \"" << label_ << "\"" << endl;
}

void
Dig::label (string label_)
{
    out << "L \"" << label_ << "\"" << endl;
}

void
Dig::style (int style)
{
    out << endl;
    out << "S " << style << endl;
    currStyle = style;
}

void
Dig::style (int colour, int mark)
{
    out << endl;
    out << "S2 " << colour << " " << mark << endl;
}

void
Dig::mark(int m)
{
    out << "K " << m << endl;
}

void
Dig::colourMark(int c, int m)
{
    out << endl;
    out << "S2 " << c << " " << m << endl;
}

void
Dig::circle (double x, double y, int diam, bool filled)
{
    out << (filled ? "Q " : "O ") << x << " " << y << " " << diam << endl;
}

void
Dig::circle (const lime::Point* p, int diam, bool filled)
{
    circle (p->x(), p->y(), diam, filled);
}

void
Dig::scaledCircle (
    double x, double y, 
    double val, double minVal, double maxVal,
    int minSizePixels, int maxSizePixels, bool filled
)
{
    double frac = (val - minVal) / (maxVal - minVal);
    int diam = (int) (minSizePixels + frac * (maxSizePixels - minSizePixels));
    circle (x, y, diam , filled);
}

void
Dig::nextStyle ()
{
    style (++currStyle);
}

void
Dig::nextDataset ()
{
    out << endl;
}

void
Dig::rgb (double r, double g, double b)
{
    if (r < 0) r = 0;
    if (r > 1) r = 1;
    if (g < 0) g = 0;
    if (g > 1) g = 1;
    if (b < 0) b = 0;
    if (b > 1) b = 1;

    out << "C " << r << " " << g << " " << b << endl;
}

void
Dig::colourScaleBR (double val, double max)
{
    double r = 0;
    double g = 0;
    double b = 0;
    if (max > 1e-6) {
        if (val < max / 2.) {
            double h = (val / (max / 2.));
            b = 1 - h;
            g = h;
        }
        else {
            double h = val / (max / 2.) - 1.;
            r = 1 - h;
            g = h;
        }
    }
    rgb (r, g, b);
}

void
Dig::colourScaleR (double val, double max)
{
    double r = 0;
    double g = 0;
    double b = 0;
    if (max > 1e-6) {
        r = val / max;
    }
    rgb (r, g, b);
}

void
Dig::labelPoint (double x, double y, const char* label)
{
    out << "LP " << x << " " << y <<
        " \"" << label << "\"" << endl;
    
}

void
Dig::labelPoint (double x, double y, string label)
{
    out << "LP " << x << " " << y <<
        " \"" << label << "\"" << endl;
    
}

void
Dig::labelPoint (const lime::Point* p, const char* label)
{
    labelPoint (p->x(), p->y(), label);
}

void
Dig::labelPoint (const lime::Point* p, string label)
{
    labelPoint (p->x(), p->y(), label);
}

void
Dig::showMessage (const char* message, const char* message2)
{
    out << "T \"" << message;
    if (message2 != NULL)
        out << " " << message2;
    out << "\"" << endl;
}

void
Dig::showMessage (string message)
{
    out << "T \"" << message << "\"" << endl;
}

void
Dig::showMessage (const char* message, int i)
{
    out << "T \"" << message << i << "\"" << endl;
}

void
Dig::showMessage (const char* message, double d)
{
    out << "T \"" << message << d << "\"" << endl;
}

void
Dig::moveTo (double x, double y)
{
    out << "M " << x << " " << y << endl;
}

void
Dig::moveTo (const lime::Point* p)
{
    moveTo (p->x(), p->y());
}

void
Dig::drawTo (double x, double y)
{
    out << "D " << x << " " << y << endl;
}

void
Dig::drawTo (const lime::Point* p)
{
    drawTo (p->x(), p->y());
}

void
Dig::drawArrowedTo (double x, double y)
{
    out << "A " << x << " " << y << endl;
}

void
Dig::drawDistinctTo (double x, double y)
{
    out << "DD " << x << " " << y << endl;
}

void
Dig::drawDistinctTo (const lime::Point* point)
{
    drawDistinctTo (point->x(), point->y());
}

void
Dig::draw (double x1, double y1, double x2, double y2)
{
    moveTo (x1, y1);
    drawTo (x2, y2);
}

void
Dig::box (double x1, double y1, double x2, double y2, int c)
{
    out << "B " << min(x1, x2) << " " << min (y1, y2) << " " << 
        fabs (x1 - x2) << " " << fabs (y2 - y1) << " " <<
        c << endl;
}

void
Dig::xTic (double x, const char* label)
{
    out << "XT " << x << " \"" << label << "\"" << endl;
}
void
Dig::xTic (double x, string label)
{
    out << "XT " << x << " \"" << label << "\"" << endl;
}

void
Dig::yTic (double y, const char* label)
{
    out << "YT " << y << " \"" << label << "\"" << endl;
}
void
Dig::yTic (double y, string label)
{
    out << "YT " << y << " \"" << label << "\"" << endl;
}

void
Dig::wait ()
{
    out << endl << "W" << endl;
}

void
Dig::wipe ()
{
    out << "WIPE " << endl; 
}

void
Dig::waitAndWipe ()
{
    wait();
    wipe();
}

void
Dig::close ()
{
    out.close();
}

void
Dig::display (std::ostream& out) const
{
    out << "dig writer";
}

// ------------------------

std::ostream&
operator<< (std::ostream& out, const Dig& dig)
{
    dig.display (out);
    return out;
}
