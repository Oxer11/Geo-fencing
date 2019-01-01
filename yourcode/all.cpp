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
double pgon[150][2];

bool MySearchCallback(int id)
{
    ansid.push_back(id);
    //printf("Hit data rect %d\n", id);
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