#ifndef DATASTRUCTUREPROJECT_SUBMIT_6MIXQUERY_H
#define DATASTRUCTUREPROJECT_SUBMIT_6MIXQUERY_H

#include <vector>

void SetEnvironmentFromMixQuery();

void AddPointFromMixQuery(int id, double x, double y);
void DeletePointFromMixQuery(int id);
std::vector<int> QueryPointFromMixQuery(double x, double y);

void AddPolygonFromMixQuery(int id, int n, std::vector < std::pair<double, double> > &polygon);
void DeletePolygonFromMixQuery(int id);
std::vector<int> QueryPolygonFromMixQuery(int n, std::vector < std::pair<double, double> > &polygon);

#endif //DATASTRUCTUREPROJECT_SUBMIT_6MIXQUERY_H
