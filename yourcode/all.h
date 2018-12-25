//
// Created by oxer on 18-12-9.
//

#ifndef PJ_ALL_H
#define PJ_ALL_H

#include "RTree.h"
#include "polypartition.h"
#include "kd_tree.h"
#include "quadtrees.h"
#include<cmath>
#include<vector>
#include<unordered_map>
#include<stack>

using namespace std;

extern RTree<int, double, 2, double> Rtree_point;
extern RTree<int, double, 2, double> Rtree;
extern kdtree KDtree;
extern TPPLPartition pp;
extern quadtrees Qtree;

bool MySearchCallback(int id);

bool MySearchCallbackTri(int id);

bool rayCasting(double px, double py, vector<pair<double, double>> &polygon);

#endif //PJ_ALL_H
