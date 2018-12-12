#include "submit-1AddPolygonBeforeQueryPoint.h"
#include "all.h"


void SetEnvironmentFromAddPolygonBeforeQueryPoint() {

}

std::vector<int> QueryPointFromAddPolygonBeforeQueryPoint(double x, double y) {
    ansid.clear();
    ans.clear();
    Rect search_rect(x, y, x, y);
    Rtree.Search(search_rect.min, search_rect.max, MySearchCallback);
    for (auto nowid : ansid)
        if (rayCasting(x, y, Poly[nowid]))
            ans.push_back(nowid);
    return ans;}

void AddPolygonFromAddPolygonBeforeQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
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
