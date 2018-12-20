#include "submit-6MixQuery.h"
#include "all.h"

void SetEnvironmentFromMixQuery() {
    KDtree.Init();
}

void AddPointFromMixQuery(int id, double x, double y) {
    KDtree.T = Point(id, x, y);
    KDtree.Solve(0);
    RPoint[id] = make_pair(x, y);
}

void DeletePointFromMixQuery(int id) {
    pair<double, double> now = RPoint[id];
    KDtree.T = Point(id, now.first, now.second);
    KDtree.erase_id = id;
    KDtree.Solve(1);
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
    //printf("%d\n", results.size());
    for (auto it : results)
    {
        Triangle tri;
        tri.a = make_pair(it[0].x, it[0].y);
        tri.b = make_pair(it[1].x, it[1].y);
        tri.c = make_pair(it[2].x, it[2].y);
        KDtree.tri = tri;
        KDtree.Solve(2);
    }
    for (auto id : ans_id)
        ans.push_back(id.first);
    return ans;
}

