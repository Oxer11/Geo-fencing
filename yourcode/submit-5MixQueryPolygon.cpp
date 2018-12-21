//
// Created by zhang on 18-12-4.
//

#include "submit-5MixQueryPolygon.h"
#include "all.h"

void SetEnvironmentFromMixQueryPolygon() {

}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    Rect R = Rect(x, y, x, y);
    RPoint[id] = make_pair(x, y);
    Rtree_point.Insert(R.min, R.max, id);
}

void DeletePointFromMixQueryPolygon(int id) {
    pair<double, double> now = RPoint[id];
    Rect R = Rect(now.first, now.second, now.first, now.second);
    Rtree_point.Remove(R.min, R.max, id);
    RPoint.erase(id);
}

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector<std::pair<double, double> > &polygon) {

    ans_id.clear();
    ans.clear();
    list<TPPLPoly> polys, results;
    TPPLPoly poly;
    poly.Init(n);
    for (int i=0;i<n;i++)
    {
        poly[i].x = polygon[i].first;
        poly[i].y = polygon[i].second;
    }
    polys.push_back(poly);
    if (!pp.Triangulate_MONO(&polys, &results))
        puts("Error in Triangulation!");
    for (auto now : results)
    {
        double mnx = MAX_POS, mny = MAX_POS, mxx = -MAX_POS, mxy = -MAX_POS;
        mnx = min(now[0].x, min(now[1].x, now[2].x));
        mny = min(now[0].y, min(now[1].y, now[2].y));
        mxx = max(now[0].x, max(now[1].x, now[2].x));
        mxy = max(now[0].y, max(now[1].y, now[2].y));
        TRI.a = make_pair(now[0].x, now[0].y);
        TRI.b = make_pair(now[1].x, now[1].y);
        TRI.c = make_pair(now[2].x, now[2].y);
        Rect search_rect(mnx, mny, mxx, mxy);
        Rtree_point.Search(search_rect.min, search_rect.max, MySearchCallbackTri);
    }
    for (auto id : ans_id)
        ans.push_back(id.first);
    sort(ans.begin(), ans.end());
    return ans;
}
