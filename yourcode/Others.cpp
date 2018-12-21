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

bool IntersectRect(Rect a, Rect b)
{
    if (max(a.min[0], b.min[0]) - min(a.max[0], b.max[0]) > 1e-8
    || max(a.min[1], b.min[1]) - min(a.max[1], b.max[1]) > 1e-8)
        return false;
    else return true;
}