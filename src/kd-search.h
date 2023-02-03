#ifndef KDSEARCH_H
#define KDSEARCH_H

#include "kd-tree.h"

std::vector<int> findNN(KDTree tree, const std::vector<int> &point);

// return the eucledian distance of two vecotrs
double eucledian_distance(std::vector<int> point1, std::vector<int> point2);

#endif // KDSEARCH_H