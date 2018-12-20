//
// Created by oxer on 18-12-13.
//

#ifndef MAIN_TRIANGLE_H
#define MAIN_TRIANGLE_H
#include<cmath>
#include<vector>
#include<unordered_map>
#include<stack>
#define eps 1e-8

using namespace std;

/*pair相加*/
template<class Ty1,class Ty2>
inline const pair<Ty1,Ty2> operator+(const pair<Ty1, Ty2>&p1, const pair<Ty1, Ty2>&p2)
{
    pair<Ty1, Ty2> ret;
    ret.first = p1.first + p2.first;
    ret.second = p1.second + p2.second;
    return ret;
}
/*pair相减*/
template<class Ty1, class Ty2>
inline const pair<Ty1, Ty2> operator-(const pair<Ty1, Ty2>&p1, const pair<Ty1, Ty2>&p2)
{
    pair<Ty1, Ty2> ret;
    ret.first = p1.first - p2.first;
    ret.second = p1.second - p2.second;
    return ret;
}

/*pair点乘*/
template<class Ty1, class Ty2>
inline const double operator*(const pair<Ty1, Ty2>&p1, const pair<Ty1, Ty2>&p2)
{
    return p1.first*p2.first + p1.second*p2.second;
}

struct Triangle
{
    pair<double, double> a, b, c;
    //bool is_bound_a, is_bound_b, is_bound_c;
};

bool PointOnSegment(double x, double y, pair<double, double> P1, pair<double, double> P2);

//https://www.cnblogs.com/wuwangchuxin0924/p/6218494.html
bool IntersectSegments(pair<double, double> a, pair<double, double> b, pair<double, double> c, pair<double, double> d);

//http://www.cnblogs.com/graphics/archive/2010/08/05/1793393.html
bool PointInTriangle(double x, double y, Triangle tri);

bool RectInTriangle(double mnx, double mny, double mxx, double mxy, Triangle tri);

bool IntersectRectTri(double mnx, double mny, double mxx, double mxy, Triangle tri);

#endif //MAIN_TRIANGLE_H
