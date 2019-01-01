#include "submit-6MixQuery.h"
#include "all.h"

void SetEnvironmentFromMixQuery() {

}

void AddPointFromMixQuery(int id, double x, double y) {
    Point[Point_cnt] = {x, y};
    Point_id[Point_cnt] = id;
    Point_cnt ++;
}

void DeletePointFromMixQuery(int id) {
    is_erase_Point[id] = 1;
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    ans.clear();
    double point[2];
    point[0] = x, point[1] = y;
    for (int i = 0; i < Poly_cnt; i++)
        if (GridTest(&PolyGrid[i], point))
            if (!is_erase_Poly[Poly_id[i]])
                ans.push_back(Poly_id[i]);
    return ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    for (int i = 0; i < n; i++)
        pgon[i][0] = polygon[i].first,
        pgon[i][1] = polygon[i].second;
    GridSetup(pgon, n, Grid_Resolution, &PolyGrid[Poly_cnt]);
    Poly_id[Poly_cnt] = id;
    Poly_cnt ++;
}

void DeletePolygonFromMixQuery(int id) {
    is_erase_Poly[id] = 1;
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
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
            if (!is_erase_Point[Point_id[i]])
                ans.push_back(Point_id[i]);
    }
    GridCleanup(&grid_set);
    return ans;
}

