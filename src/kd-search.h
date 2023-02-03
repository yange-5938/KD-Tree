#ifndef KDSEARCH_H
#define KDSEARCH_H

#include "kd-tree.h"

class SearchStrategies
{
private:
    static void findNN(const KDNode *node, const std::vector<int> &point, double &best_dist, std::shared_ptr<KDNode> &curr_best);

public:
    // find the nearest neighbor of a point in given points
    static std::vector<int> findNN(const KDTree &tree, const std::vector<int> &point);
};

// return the eucledian distance of two vecotrs
double eucledian_distance(std::vector<int> point1, std::vector<int> point2);

#endif // KDSEARCH_H
