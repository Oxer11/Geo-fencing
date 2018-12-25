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
    if (n>=0)
    {
        double s = -0.5*(polygon[0].second+polygon[n-1].second)*(polygon[0].first-polygon[n-1].first);
        for (int i=0;i<n-1;i++)
            s += -0.5*(polygon[i+1].second+polygon[i].second)*(polygon[i+1].first-polygon[i].first);
        if (s<0.0)
        {
            for (int i=0;i<n/2;i++) swap(polygon[i], polygon[n-i-1]);
        }
        list<TPPLPoly> polys, results;
        TPPLPoly poly;
        poly.Init(n);
        for (int i=0;i<n;i++)
        {
            poly[i].x = polygon[i].first;
            poly[i].y = polygon[i].second;
        }
        polys.push_back(poly);
        if (!pp.Triangulate_EC(&poly, &results))
            printf("Error in Triangulation! cnt:%d area:%.3lf\n", n, s);
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
    }
    else
    {
        double mnx = MAX_POS, mny = MAX_POS, mxx = -MAX_POS, mxy = -MAX_POS;
        for (auto now : polygon)
        {
            if (now.first < mnx) mnx = now.first;
            if (now.second < mny) mny = now.second;
            if (now.first > mxx) mxx = now.first;
            if (now.second > mxy) mxy = now.second;
        }
        KDtree.rectangle.min[0] = mnx;
        KDtree.rectangle.min[1] = mny;
        KDtree.rectangle.max[0] = mxx;
        KDtree.rectangle.max[1] = mxy;
        KDtree.Solve(3);
        for (auto nowid : ans_id)
        {
            pair<double, double> now = RPoint[nowid.first];
            if (rayCasting(now.first, now.second, polygon))
                ans.push_back(nowid.first);
        }
    }
    return ans;
}

