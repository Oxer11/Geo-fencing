//
// Created by oxer on 18-12-13.
//

#include "Others.h"

unordered_map<int, int> ans_id;
unordered_map<int, Rect> RPoly;
unordered_map<int, vector<pair<double, double>>> Poly;
vector<int> ansid, ans;
unordered_map<int, pair<double, double>> RPoint;

int cur;
int n,m,cnt;
Point p[20000010];

bool IntersectRect(double mnx, double mny, double mxx, double mxy, Rect b)
{
    if (max(mnx, b.min[0]) - min(mxx, b.max[0]) > 1e-8
    || max(mny, b.min[1]) - min(mxy, b.max[1]) > 1e-8)
        return false;
    else return true;
}