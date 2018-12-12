#include "submit-2AddPointBeforeQueryPolygon.h"
#include "all.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {

}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    Rect R = Rect(x, y, x, y);
    RPoint[id] = make_pair(x, y);
    Rtree_point.Insert(R.min, R.max, id);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
    ansid.clear();
    ans.clear();
    double mnx = MAX_POS, mny = MAX_POS, mxx = -MAX_POS, mxy = -MAX_POS;
    for (auto now : polygon)
    {
        if (now.first < mnx) mnx = now.first;
        if (now.second < mny) mny = now.second;
        if (now.first > mxx) mxx = now.first;
        if (now.second > mxy) mxy = now.second;
    }
    Rect search_rect(mnx, mny, mxx, mxy);
    Rtree_point.Search(search_rect.min, search_rect.max, MySearchCallback);
    for (auto nowid : ansid)
    {
        pair<double, double> now = RPoint[nowid];
        if (rayCasting(now.first, now.second, polygon))
            ans.push_back(nowid);
    }
    return ans;}
