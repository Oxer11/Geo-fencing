#include "submit-2AddPointBeforeQueryPolygon.h"
#include "all.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {

}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    //Rect R = Rect(x, y, x, y);
    //RPoint[id] = make_pair(x, y);
    //Rtree_point.Insert(R.min, R.max, id);
    Point.push_back(make_pair(x, y));
    Point_id.push_back(id);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
    ansid.clear();
    ans.clear();
    /*double mnx = MAX_POS, mny = MAX_POS, mxx = -MAX_POS, mxy = -MAX_POS;
    for (auto now : polygon) {
        if (now.first < mnx) mnx = now.first;
        if (now.second < mny) mny = now.second;
        if (now.first > mxx) mxx = now.first;
        if (now.second > mxy) mxy = now.second;
    }
    Rect search_rect(mnx, mny, mxx, mxy);
    Rtree_point.Search(search_rect.min, search_rect.max, MySearchCallback);*/
    GridSet grid_set;
    for (int i = 0; i < n; i++)
        pgon[i][0] = polygon[i].first,
        pgon[i][1] = polygon[i].second;
    GridSetup(pgon, n, Grid_Resolution, &grid_set);
    for (int i = 0; i<Point.size(); i++) {
        //pair<double, double> now = RPoint[nowid];
        double point[2];
        point[0] = Point[i].first, point[1] = Point[i].second;
        if (GridTest(&grid_set, point))
            ans.push_back(Point_id[i]);
    }
    GridCleanup(&grid_set);
    return ans;
}
