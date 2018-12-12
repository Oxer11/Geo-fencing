#ifndef DATASTRUCTUREPROJECT_SUBMIT_4MIXQUERYPOINT_H
#define DATASTRUCTUREPROJECT_SUBMIT_4MIXQUERYPOINT_H

#include <vector>

void SetEnvironmentFromMixQueryPoint();

std::vector<int> QueryPointFromMixQueryPoint(double x, double y);

void AddPolygonFromMixQueryPoint(int id, int n, std::vector < std::pair<double, double> > &polygon);
void DeletePolygonFromMixQueryPoint(int id);

#endif //DATASTRUCTUREPROJECT_SUBMIT_4MIXQUERYPOINT_H
