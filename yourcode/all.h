//
// Created by oxer on 18-12-9.
//

#ifndef PJ_ALL_H
#define PJ_ALL_H

#include "Others.h"
#include "RTree.h"
#include "ptinpoly.h"
#include<cmath>
#include<vector>
#include<unordered_map>
#define MAX_POS 5000000
#define Grid_Resolution 100

using namespace std;

extern RTree<int, double, 2, double> Rtree_point;
extern unordered_map<int, pair<double, double>> RPoint;

extern RTree<int, double, 2, double> Rtree;
extern unordered_map<int, Rect> RPoly;
extern unordered_map<int, vector<pair<double, double>>> Poly;
extern vector<int> ansid, ans;
extern double pgon[150][2];
extern vector<pair<double, double> > Point;
extern vector<int> Point_id;

bool MySearchCallback(int id);

bool rayCasting(double px, double py, vector<pair<double, double>> &polygon);

#endif //PJ_ALL_H
