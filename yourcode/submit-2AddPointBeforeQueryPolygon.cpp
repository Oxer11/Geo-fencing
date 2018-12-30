#include "submit-2AddPointBeforeQueryPolygon.h"
#include "all.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {
	KDtree.Init();
}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    KDtree.T = Point(id, x, y);
    KDtree.Solve(0);
    RPoint[id] = make_pair(x, y);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
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
