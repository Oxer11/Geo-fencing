#ifndef DATASTRUCTUREPROJECT_SUBMIT_5MIXQUERYPOLY_H
#define DATASTRUCTUREPROJECT_SUBMIT_5MIXQUERYPOLY_H

#include <vector>

void SetEnvironmentFromMixQueryPolygon();

void AddPointFromMixQueryPolygon(int id, double x, double y);
void DeletePointFromMixQueryPolygon(int id);

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector < std::pair<double, double> > &polygon);

#endif //DATASTRUCTUREPROJECT_SUBMIT_5MIXQUERYPOLY_H
