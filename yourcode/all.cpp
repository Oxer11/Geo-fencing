//
// Created by oxer on 18-12-9.
//

#include "all.h"

RTree<int, double, 2, double> Rtree_point;
unordered_map<int, pair<double, double>> RPoint;

RTree<int, double, 2, double> Rtree;
unordered_map<int, Rect> RPoly;
unordered_map<int, vector<pair<double, double>>> Poly;
vector<int> ansid, ans;
unordered_map<int, int> ans_id;

bool MySearchCallback(int id)
{
    ansid.push_back(id);
    return true; // keep going
}

bool rayCasting(double px, double py, vector<pair<double, double>> &polygon)
{
    bool flag = false;

    for(int i = 0, l = polygon.size(), j = l - 1; i < l; j = i, i++)
    {
        double sx = polygon[i].first, sy = polygon[i].second, tx = polygon[j].first, ty = polygon[j].second;

        // 点与多边形顶点重合
        if((sx == px && sy == py) || (tx == px && ty == py)) return false;

        // 判断线段两端点是否在射线两侧
        if((sy < py && ty >= py) || (sy >= py && ty < py))
        {
            // 线段上与射线 Y 坐标相同的点的 X 坐标
            double x = sx + (py - sy) * (tx - sx) / (ty - sy);
            // 点在多边形的边上
            if(x == px) return false;
            // 射线穿过多边形的边界
            if(x > px) flag = !flag;
        }
    }

    // 射线穿过多边形边界的次数为奇数时点在多边形内
    return flag;
}

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

//http://www.cnblogs.com/graphics/archive/2010/08/05/1793393.html
bool PointInTriangle(double x, double y, Triangle tri)
{
    if (tri.is_bound_a && PointOnSegment(x, y, tri.a, tri.b)) return false;
    if (tri.is_bound_b && PointOnSegment(x, y, tri.b, tri.c)) return false;
    if (tri.is_bound_c && PointOnSegment(x, y, tri.c, tri.a)) return false;

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
        return false;
    if (tri.c.first>=mnx && tri.c.first<=mxx && tri.c.second>=mny && tri.c.second<=mxy)
        return false;
    return PointInTriangle(mnx, mny, tri)
        || PointInTriangle(mnx, mxy, tri)
        || PointInTriangle(mxx, mny, tri)
        || PointInTriangle(mxx, mxy, tri);
}

