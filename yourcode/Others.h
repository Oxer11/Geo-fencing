//
// Created by oxer on 18-12-9.
//

#ifndef PJ_OTHERS_H
#define PJ_OTHERS_H

#include<unordered_map>
#include<vector>
#include<cmath>

using namespace std;

struct Rect {
    Rect()  {}

    Rect(double a_minX, double a_minY, double a_maxX, double a_maxY)
    {
        min[0] = a_minX;
        min[1] = a_minY;

        max[0] = a_maxX;
        max[1] = a_maxY;
    }


    double min[2];
    double max[2];
};

extern int cur;

struct Point
{
    double d[2];
    int id;
    Point(){};
    Point(int t, double x, double y) {id=t,d[0]=x,d[1]=y;}
    bool operator < (const Point &n1) const
    {
        return d[cur]<n1.d[cur]
            || (fabs(d[cur]-n1.d[cur])<1e-8 && d[cur^1]<n1.d[cur^1]);
    }
};

extern unordered_map<int, int> ans_id;
extern unordered_map<int, Rect> RPoly;
extern unordered_map<int, vector<pair<double, double>>> Poly;
extern vector<int> ansid, ans;
extern unordered_map<int, pair<double, double>> RPoint;

extern int n,m,cnt;
extern Point p[20000010];

bool IntersectRect(double mnx, double mny, double mxx, double mxy, Rect b);

#endif //PJ_OTHERS_H
