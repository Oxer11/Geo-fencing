//
// Created by zhang on 18-12-4.
//

#include "submit-5MixQueryPolygon.h"
#include "all.h"

void SetEnvironmentFromMixQueryPolygon() {

}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    Point[Point_cnt] = {x, y};
    Point_id[Point_cnt] = id;
    Point_cnt ++;
}

void DeletePointFromMixQueryPolygon(int id) {
    is_erase_Point[id%mod] = 1;
}

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector<std::pair<double, double> > &polygon) {
    ans.clear();
    GridSet grid_set;
    for (int i = 0; i < n; i++)
        pgon[i][0] = polygon[i].first,
        pgon[i][1] = polygon[i].second;
    GridSetup(pgon, n, Grid_Resolution, &grid_set);
    for (int i = 0; i<Point_cnt; i++) {
        double point[2];
        point[0] = Point[i].first, point[1] = Point[i].second;
        if (GridTest(&grid_set, point))
            if (!is_erase_Point[Point_id[i]%mod])
              ans.push_back(Point_id[i]);
    }
    GridCleanup(&grid_set);
    return ans;
}
