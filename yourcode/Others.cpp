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