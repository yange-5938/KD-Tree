#include "cmath"
#include "memory"

#include "kd-search.h"
#include "helper.h"

std::vector<int> SearchStrategies::findNN(const KDTree &tree, const std::vector<int> &point)
{
    double inf = std::numeric_limits<double>::infinity();
    auto curr_best = std::make_shared<KDNode>();
    findNN(tree.root, point, inf, curr_best);
    return curr_best->vector;
}

void SearchStrategies::findNN(const KDNode *node, const std::vector<int> &point, double &best_dist, std::shared_ptr<KDNode> &curr_best)
{
    if (!node)
    {
        return;
    }

    if (double dist = eucledian_distance(node->vector, point); dist < best_dist)
    {
        *curr_best = *node;
        best_dist = dist;
    }
    auto cuttingEdge = node->cuttingEdge;
    char choice = 0;
    auto el1 = point[cuttingEdge];        // TODO: use better descriptive names
    auto el2 = node->vector[cuttingEdge]; // TODO: use better descriptive names
    if (el1 <= el2)
    {
        findNN(node->left, point, best_dist, curr_best);
    }
    else
    {
        choice = 1;
        findNN(node->right, point, best_dist, curr_best);
    }

    if (abs(el2 - el1) <= best_dist)
    {
        if (choice)
        {
            findNN(node->left, point, best_dist, curr_best);
        }
        else
        {
            findNN(node->right, point, best_dist, curr_best);
        }
    }
}

double eucledian_distance(std::vector<int> point1, std::vector<int> point2)
{
    double sum = 0;
    auto el1 = point1.begin();
    auto el2 = point2.begin();
    while (el1 != point1.end())
    {
        sum += pow((*el2 - *el1), 2);
        el1 = std::next(el1);
        el2 = std::next(el2);
    }
    return sqrt(sum);
}
