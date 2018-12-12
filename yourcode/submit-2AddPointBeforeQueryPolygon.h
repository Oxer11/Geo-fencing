#ifndef DATASTRUCTUREPROJECT_SUBMIT_2ADDPOINTBEFOREQUERYPOLY_H
#define DATASTRUCTUREPROJECT_SUBMIT_2ADDPOINTBEFOREQUERYPOLY_H

#include <vector>

void SetEnvironmentFromAddPointBeforeQueryPolygon();

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y);

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon);

#endif //DATASTRUCTUREPROJECT_SUBMIT_2ADDPOINTBEFOREQUERYPOLY_H
