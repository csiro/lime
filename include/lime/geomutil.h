#pragma once

/* Use of this code is is subject to agreement to the
   CSIRO Open Source Software Licence Agreement
   as set out in the file ../../LICENCE.md
*/


namespace lime {

    class Point;
    class Line;
    
    double dist (double x1, double y1, double x2, double y2);
    int dist (int x1, int y1, int x2, int y2);
    double toRadians (double degrees);
    double toDegrees (double radians);
    
    /**
       Interpolate along a line between two points.
       @param a The first point
       @param b The second point
       @param frac How far along the line ab we want.  0 is the point "a";
       1 is the point "b"; 0.5 is halfway
       @return A point "frac" along the line ab
    */
    Point* interpolate (
        const Point* a, const Point* b, double frac, Point* result
    );


    /* What value of f makes if true that 'c' is f times
       the dist between a and b
    */
    double invInterpolate (
        const Point* a, const Point* b, const Point* c
    );
    
    
    /** Find a point dist away from from in the direction of vec */
    Point* add (
        const Point* from, const Point* vec, double dist, Point* result
    );
    /** Find a point dist away from from in the direction of vec */
    Point* add (
        Point* from, const Point* vec, double dist = 1.0
    );
    
    /** Find a unit vector giving the direction from from towards to.
     *  Put the result in vec */
    Point* unitVec (const Point* from, const Point* to, Point* vec);

    /** Scale the point (multiply) by the given scalar. Updates in-situ */
    Point* scale (Point* pt, double scale);

    /** Return the point on the line closest to point
     *  Places the result in result. Returns result.
     *  From http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
     */
    Point* closestPoint (
        const Line* line, const Point* target, Point* result
    );

    /** Find the point where two segments intersect.
     *  Returns false if they do not intersect
     *  From http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/ 
     */
    bool segIntersection (const Line* seg1, const Line* seg2, Point* result);

    /** Return the *clockwise* angle ABC in radians */
    double angle (const Point* a, const Point* b, const Point* c);

    /** Great circle distance in metres between two lat/long positions */
    double greatCircleDistMetres (
        double lat1, double long1, double lat2, double long2
    );
    /** Great circle distance in metres between two Points
        (x,y) is read as (lat/long)
    */
    double greatCircleDistLatLongMetres (const Point* from, const Point* to);
    /** Great circle distance in metres between two Points
        (x,y) is read as (long/lat)
    */
    double greatCircleDistLongLatMetres (const Point* from, const Point* to);
    
    /** Great circle distance in nautical miles between two Points
        (x,y) is read as (lat/long)
    */
    double greatCircleDistNM (const Point* from, const Point* to);
    

} // namespace

