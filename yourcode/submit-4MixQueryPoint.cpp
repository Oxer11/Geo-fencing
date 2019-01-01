#include "submit-4MixQueryPoint.h"
#include "all.h"

void SetEnvironmentFromMixQueryPoint() {

}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    ansid.clear();
    ans.clear();
    Rect search_rect(x, y, x, y);
    Rtree.Search(search_rect.min, search_rect.max, MySearchCallback);

    double point[2];
    point[0] = x, point[1] = y;
    for (int i = 0; i < ansid.size(); i++)
    {
        int now = ansid[i];
        if (GridTest(&PolyGrid[now], point))
            if (!is_erase_Poly[Poly_id[now]])
                ans.push_back(Poly_id[now]);
    }

    return ans;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    double mnx = MAX_POS, mny = MAX_POS, mxx = -MAX_POS, mxy = -MAX_POS;
    for (auto now : polygon)
    {
        if (now.first < mnx) mnx = now.first;
        if (now.second < mny) mny = now.second;
        if (now.first > mxx) mxx = now.first;
        if (now.second > mxy) mxy = now.second;
    }
    Rect R = Rect(mnx, mny, mxx, mxy);
    Rtree.Insert(R.min, R.max, Poly_cnt);

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
