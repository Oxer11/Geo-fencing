#include "submit-4MixQueryPoint.h"
#include "all.h"

void SetEnvironmentFromMixQueryPoint() {

}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    ans.clear();
    double point[2];
    point[0] = x, point[1] = y;
    for (int i = 0; i < Poly_cnt; i++)
        if (GridTest(&PolyGrid[i], point))
            if (!is_erase_Poly[Poly_id[i]])
            ans.push_back(Poly_id[i]);
    return ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    for (int i = 0; i < n; i++)
        pgon[i][0] = polygon[i].first,
        pgon[i][1] = polygon[i].second;
    GridSetup(pgon, n, Grid_Resolution, &PolyGrid[Poly_cnt]);
    Poly_id[Poly_cnt] = id;
    Poly_cnt ++;
}

void DeletePolygonFromMixQueryPoint(int id) {
    is_erase_Poly[id] = 1;
}
