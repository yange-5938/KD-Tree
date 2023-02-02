#ifndef KDSEARCH_H
#define KDSEARCH_H

#include "kd-tree.h"

std::vector<int> findMin(int dim, KDTree tree);
std::vector<int> findNN(KDTree tree, const std::vector<int> &point);

double eucledian_distance(std::vector<int> point1, std::vector<int> point2);

std::unique_ptr<KDTree> createKDTreeFromFile(std::string file_name, int dim);

#endif // KDSEARCH_H