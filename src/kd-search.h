#pragma once

#include "kd-tree.h"

class SearchStrategies
{
public:
    static std::vector<int> findMin(int dim, KDTree tree);
    static std::vector<int> findNN(KDTree tree, const std::vector<int> &point);

private:
    // private method returns the vector which has the minimum number of the given dimension
    static KDNode *findMin(int dim, KDNode *leaf);
    // private returns minimum KDNode in the vector
    static KDNode *minOfPoints(const std::vector<KDNode *> &points, int dim);
    static void findNN(const KDNode *node, const std::vector<int> &point, double &best_dist, std::shared_ptr<KDNode>& curr_best);
    static double eucledian_distance(std::vector<int> point1, std::vector<int> point2);
};