//
// Created by oxer on 18-12-13.
//

#include "Triangle.h"

bool PointOnSegment(double x, double y, pair<double, double> P1, pair<double, double> P2)
{
    pair<double, double> seg = P2 - P1;
    pair<double, double> PQ = make_pair(x-P1.first, y-P1.second);

    if (fabs(seg.first*PQ.second-seg.second*PQ.first)>eps) return false;

    if (P1.first <= x && x <= P2.first || P2.first<= x && x<=P1.first)
        if (P1.second <= y && y <= P2.second || P2.second<= y && y<=P1.second)
            return true;

    return false;
}

bool PointInTriangle(double x, double y, Triangle tri)
{
    //if (tri.is_bound_a && PointOnSegment(x, y, tri.a, tri.b)) return false;
    //if (tri.is_bound_b && PointOnSegment(x, y, tri.b, tri.c)) return false;
    //if (tri.is_bound_c && PointOnSegment(x, y, tri.c, tri.a)) return false;

    pair<double, double> v0 = tri.c - tri.a;
    pair<double, double> v1 = tri.b - tri.a;
    pair<double, double> v2 = make_pair(x-tri.a.first, y-tri.a.second);

    double dot00 = v0*v0;
    double dot01 = v0*v1;
    double dot02 = v0*v2;
    double dot11 = v1*v1;
    double dot12 = v1*v2;

    double inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;

    double u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
    if (u < 0 || u > 1) // if u out of range, return directly
        return false ;

    double v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
    if (v < 0 || v > 1) // if v out of range, return directly
        return false;

    return u + v <= 1 ;
}

bool RectInTriangle(double mnx, double mny, double mxx, double mxy, Triangle tri)
{
    return PointInTriangle(mnx, mny, tri)
           && PointInTriangle(mnx, mxy, tri)
           && PointInTriangle(mxx, mny, tri)
           && PointInTriangle(mxx, mxy, tri);
}

bool IntersectRectTri(double mnx, double mny, double mxx, double mxy, Triangle tri)
{
    if (tri.a.first>=mnx && tri.a.first<=mxx && tri.a.second>=mny && tri.a.second<=mxy)
        return true;
    if (tri.b.first>=mnx && tri.b.first<=mxx && tri.b.second>=mny && tri.b.second<=mxy)
        return true;
    if (tri.c.first>=mnx && tri.c.first<=mxx && tri.c.second>=mny && tri.c.second<=mxy)
        return true;
    return PointInTriangle(mnx, mny, tri)
           || PointInTriangle(mnx, mxy, tri)
           || PointInTriangle(mxx, mny, tri)
           || PointInTriangle(mxx, mxy, tri);
}