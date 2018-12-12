#ifndef DATASTRUCTUREPROJECT_SUBMIT_3ADDBEFOREQUERY_H
#define DATASTRUCTUREPROJECT_SUBMIT_3ADDBEFOREQUERY_H

#include <vector>

void SetEnvironmentFromAddBeforeQuery();

void AddPointFromAddBeforeQuery(int id, double x, double y);
std::vector<int> QueryPointFromAddBeforeQuery(double x, double y);

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon);
std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector < std::pair<double, double> > &polygon);

#endif //DATASTRUCTUREPROJECT_SUBMIT_3ADDBEFOREQUERY_H
