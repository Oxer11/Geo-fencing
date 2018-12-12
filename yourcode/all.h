//
// Created by oxer on 18-12-9.
//

#ifndef PJ_ALL_H
#define PJ_ALL_H

#include "Others.h"
#include "RTree.h"
#include<cmath>
#include<vector>
#include<unordered_map>
#include<stack>
#define MAX_POS 5000000
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
    bool is_bound_a, is_bound_b, is_bound_c;
};

extern RTree<int, double, 2, double> Rtree_point;
extern unordered_map<int, pair<double, double>> RPoint;

extern RTree<int, double, 2, double> Rtree;
extern unordered_map<int, Rect> RPoly;
extern unordered_map<int, vector<pair<double, double>>> Poly;
extern vector<int> ansid, ans;
extern unordered_map<int, int> ans_id;

bool MySearchCallback(int id);

bool rayCasting(double px, double py, vector<pair<double, double>> &polygon);

bool PointInTriangle(double x, double y, Triangle tri);

bool RectInTriangle(double mnx, double mny, double mxx, double mxy, Triangle tri);

bool IntersectRectTri(double mnx, double mny, double mxx, double mxy, Triangle tri);

#endif //PJ_ALL_H
