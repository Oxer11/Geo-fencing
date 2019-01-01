#include "submit-6MixQuery.h"
#include "all.h"

void SetEnvironmentFromMixQuery() {

}

void AddPointFromMixQuery(int id, double x, double y) {
    Rect R = Rect(x, y, x, y);
    RPoint[id] = make_pair(x, y);
    Rtree_point.Insert(R.min, R.max, id);
}

void DeletePointFromMixQuery(int id) {
    pair<double, double> now = RPoint[id];
    Rect R = Rect(now.first, now.second, now.first, now.second);
    Rtree_point.Remove(R.min, R.max, id);
    RPoint.erase(id);
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    ansid.clear();
    ans.clear();
    Rect search_rect(x, y, x, y);
    Rtree.Search(search_rect.min, search_rect.max, MySearchCallback);
    for (auto nowid : ansid)
      if (rayCasting(x, y, Poly[nowid]))
          ans.push_back(nowid);
    return ans;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    double mnx = MAX_POS, mny = MAX_POS, mxx = -MAX_POS, mxy = -MAX_POS;
    for (auto now : polygon)
    {
        if (now.first < mnx) mnx = now.first;
        if (now.second < mny) mny = now.second;
        if (now.first > mxx) mxx = now.first;
        if (now.second > mxy) mxy = now.second;
    }
    Rect R = Rect(mnx, mny, mxx, mxy);
    RPoly[id] = R;
    Poly[id] = polygon;
    Rtree.Insert(R.min, R.max, id);
}

void DeletePolygonFromMixQuery(int id) {
    Rect R = RPoly[id];
    Rtree.Remove(R.min, R.max, id);
    RPoly.erase(id);
    Poly.erase(id);
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
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
    return ans;
}

