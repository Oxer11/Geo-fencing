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

bool IntersectSegments(pair<double, double> a, pair<double, double> b, pair<double, double> c, pair<double, double> d)
{
    /*
         快速排斥：
         两个线段为对角线组成的矩形，如果这两个矩形没有重叠的部分，那么两条线段是不可能出现重叠的
    */
    if(!(min(a.first,b.first)<=max(c.first,d.first)
    && min(c.second,d.second)<=max(a.second,b.second)
    && min(c.first,d.first)<=max(a.first,b.first)
    && min(a.second,b.second)<=max(c.second,d.second)))
        //这里的确如此，这一步是判定两矩形是否相交
        //1.线段ab的低点低于cd的最高点（可能重合） 2.cd的最左端小于ab的最右端（可能重合）
        //3.cd的最低点低于ab的最高点（加上条件1，两线段在竖直方向上重合） 4.ab的最左端小于cd的最右端（加上条件2，两直线在水平方向上重合）
        //综上4个条件，两条线段组成的矩形是重合的
        /*特别要注意一个矩形含于另一个矩形之内的情况*/
        return false;
    /*
    跨立实验：
    如果两条线段相交，那么必须跨立，就是以一条线段为标准，另一条线段的两端点一定在这条线段的两段
    也就是说a b两点在线段cd的两端，c d两点在线段ab的两端
    */
    double u,v,w,z;//分别记录两个向量
    u=(c.first-a.first)*(b.second-a.second)-(b.first-a.first)*(c.second-a.second);
    v=(d.first-a.first)*(b.second-a.second)-(b.first-a.first)*(d.second-a.second);
    w=(a.first-c.first)*(d.second-c.second)-(d.first-c.first)*(a.second-c.second);
    z=(b.first-c.first)*(d.second-c.second)-(d.first-c.first)*(b.second-c.second);
    return (u*v<=0.00000001 && w*z<=0.00000001);
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
    if (PointInTriangle(mnx, mny, tri) || PointInTriangle(mnx, mxy, tri)
        || PointInTriangle(mxx, mny, tri) || PointInTriangle(mxx, mxy, tri))
        return true;
    pair<double, double>
        a = make_pair(tri.a.first, tri.a.second),
        b = make_pair(tri.b.first, tri.b.second),
        c = make_pair(tri.c.first, tri.c.second),
        now0 = make_pair(mnx, mny),
        now1 = make_pair(mnx, mxy),
        now2 = make_pair(mxx, mxy),
        now3 = make_pair(mxx, mny);
    return IntersectSegments(now0,now1,a,b) || IntersectSegments(now0,now1,b,c) || IntersectSegments(now0,now1,c,a)
    || IntersectSegments(now1,now2,a,b) || IntersectSegments(now1,now2,b,c) || IntersectSegments(now1,now2,c,a)
    || IntersectSegments(now2,now3,a,b) || IntersectSegments(now2,now3,b,c) || IntersectSegments(now2,now3,c,a)
    || IntersectSegments(now3,now0,a,b) || IntersectSegments(now3,now0,b,c) || IntersectSegments(now3,now0,c,a);
}