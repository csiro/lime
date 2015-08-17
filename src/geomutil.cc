
// Auto-updated timestamp
#define TIMESTAMP "Time-stamp: <2 Apr 2014 13:42:02>"

#include <stdio.h>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265359)
#endif

/** Lime string utilities */

#include "lime/geomutil.h"
#include "lime/numutil.h"

#include "lime/point.h"
#include "lime/line.h"

using namespace lime;

/**
   Utility routines for working with point class.
*/
                    
double
lime::dist (double x1, double y1, double x2, double y2)
{
    double dx = (x2 - x1);
    double dy = (y2 - y1);
    return sqrt (dx * dx + dy * dy);
}

int
lime::dist (int x1, int y1, int x2, int y2)
{
    int dx = (x2 - x1);
    int dy = (y2 - y1);
    double dist = sqrt (dx * dx + dy * dy);
    return (int) floor (dist + 0.5);
}

double
lime::toRadians (double degrees)
{
    return degrees * M_PI / 180.0;
}
double
lime::toDegrees (double radians)
{
    return radians * 180.0 / M_PI;
}

/**
   Interpolate along a line between two points.
   @param a The first point
   @param b The second point
   @param frac How far along the line ab we want.  0 is the point "a";
   1 is the point "b"; 0.5 is halfway
   @return A point "frac" along the line ab
*/
Point*
lime::interpolate (
    const Point* a, const Point* b, double frac, Point* result
)
{
    result->set(
        a->x + (b->x - a->x) * frac,
        a->y + (b->y - a->y) * frac
    );
    return result;
}

/* What value of f makes if true that 'c' is f times
   the dist between a and b
*/
double
lime::invInterpolate (
    const Point* a, const Point* b, const Point* c
)
{
    double fx = (c->x - a->x) / (b->x - a->x);
    double fy = (c->y - a->y) / (b->y - a->y);
    double f = limeMin (fx, fy);
    
    return f;
}

/** Find a point dist away from from in the direction of vec
    Can call with result == from
 */
Point*
lime::add (
    const Point* from, const Point* vec, double dist, Point* result
)
{
    result->set (
        from->x + vec->x * dist,
        from->y + vec->y * dist
    );
    return result;
}

/** Find a point dist away from from in the direction of vec
    Updates from in-situ
 */
Point*
lime::add (
    Point* from, const Point* vec, double dist
)
{
    return add (from, vec, dist, from);
}
    
/** Find a unit vector giving the direction from from towards to.
 *  Put the result in vec
 */
Point*
lime::unitVec (const Point* from, const Point* to, Point* vec)
{
    vec->set (to->x - from->x, to->y - from->y);
    double len = vec->distTo (0.0, 0.0);
    vec->set (vec->x/len, vec->y/len);
    return vec;
}

/** Scale the point (multiply) by the given scalar. Updates in-situ */
Point*
lime::scale (Point* pt, double scale)
{
    pt->set (pt->x * scale, pt->y * scale);
    return pt;
}

/** Return the point on the line closest to point
 *  Places the result in result. Returns result.
 *  From http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
 */
Point*
lime::closestPoint (
    const Line* line, const Point* target, Point* result
)
{
    //Line is 1-2, point is 3
    double x1 = line->x1();
    double y1 = line->y1();
    double x2 = line->x2();
    double y2 = line->y2();
    double x3 = target->x;
    double y3 = target->y;
    double len = line->p1()->distTo (line->p2());
    if (len < 0.00000001) {
        return result->copy (line->p1());
    }
    double u =
        ((x3 - x1)*(x2 - x1) + (y3 - y1)*(y2 - y1))/(len * len);
    if (u < 0)
        u = 0;
    else if (u > 1)
        u = 1;
    result->set (x1 + u * (x2 - x1), y1 + u * (y2 - y1));
    return result;
}

/** Find the point where two segments intersect.
 *  Returns false if they do not intersect
 *  From http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/ 
 */
bool
lime::segIntersection (const Line* seg1, const Line* seg2, Point* result)
{
    double x1 = seg1->x1();
    double y1 = seg1->y1();
    double x2 = seg1->x2();
    double y2 = seg1->y2();
    double x3 = seg2->x1();
    double y3 = seg2->y1();
    double x4 = seg2->x2();
    double y4 = seg2->y2();
        
    double aNumer = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    double bNumer = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
    double denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    if (fabs(denom) < 0.0001)
        return false; //Lines are parallel

    double ua = aNumer / denom;
    double ub = bNumer / denom;

    if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
        // No intersection
        return false;
    }
    interpolate (seg1->p1(), seg1->p2(), ua, result);
    return true;
}
    
/** Return the *clockwise* angle ABC in radians */
double
lime::angle (const Point* a, const Point* b, const Point* c)
{
    double theta1 =
        atan2 (a->y - b->y, a->x - b->x);
    double theta2 =
        atan2 (c->y - b->y, c->x - b->x);

    double theta = theta1 - theta2;
    if (theta < 0)
        theta += 2 * M_PI;
    
    return theta;
}


/** Great circle distance in metres between two lat/long positions
    From http://www.indo.com/distance/dist.pl
*/
double
lime::greatCircleDistMetres (
    double lat1, double long1, double lat2, double long2
)
{
    // approx radius of Earth in meters.  True radius varies from
    // 6357km (polar) to 6378km (equatorial).
    static double earthRadius = 6367000;

    lat1 = toRadians (lat1);
    long1 = toRadians (long1);
    lat2 = toRadians (lat2);
    long2 = toRadians (long2);

    double dlon = long2 - long1;
    double dlat = lat2 - lat1;

    double t1 = sin(dlat / 2);
    double t2 = sin(dlon / 2);
        
    double a = t1 * t1 + cos(lat1) * cos(lat2) * t2 * t2;
    double d = 2.0 * fabs (atan2(sqrt(a), sqrt(1 - a)));
        
    /**
       This is a simpler formula, but it's subject to rounding errors
       for small distances.  See
       http://www.census.gov/cgi-bin/geo/gisfaq?Q5.1
       double d = Math.acos(Math.sin(lat1) * Math.sin(lat2)
       + Math.cos(lat1) * Math.cos(lat2) * Math.cos(long1-long2));
    */
    return earthRadius * d;
}

/** Great circle distance in metres between two Points
    (x,y) is read as (lat/long)
*/
double
lime::greatCircleDistMetres (const Point* from, const Point* to)
{
    return
        greatCircleDistMetres (
            from->x, from->y, to->x, to->y
        );
}

double
lime::greatCircleDistNM (const Point* from, const Point* to)
{
    return greatCircleDistMetres (from, to) *  0.000539956803;
}
