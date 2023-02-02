

#include "kd-search.h"
//#include "kd-tree.h"

// private returns minimun KDNode in the vector
KDNode *SearchStrategies::minOfPoints(std::vector<KDNode *> points, int dim)
{
    KDNode *min_el = nullptr;
    for (auto point : points)
    {
        if (min_el == nullptr)
        {
            min_el = point;
        }
        else if (point != nullptr)
        {
            if (point->vector[dim] < min_el->vector[dim])
            {
                min_el = point;
            }
        }
    }
    return min_el;
}

// return the vector which has the minumun number of the given dimension
KDNode *SearchStrategies::findMin(int dim)
{
    return findMin(dim, root);
}

// private method returns the vector which has the minumun number of the given dimension
KDNode *SearchStrategies::findMin(int dim, KDNode *leaf)
{
    if (leaf == nullptr)
        return nullptr;

    if (dim == leaf->cuttingEdge)
    {
        if (leaf->left == nullptr)
            return leaf;
        else
            return findMin(dim, leaf->left);
    }
    else
    {

        return SearchStrategies::minOfPoints({findMin(dim, leaf->right),
                                    findMin(dim, leaf->left),
                                    leaf},
                                   dim);
    }
}



/*
static std::vector<int> findMin(int dim, KDTree tree);

static std::vector<int> findNN(KDTree tree, const std::vector<int> &point);

// private method returns the vector which has the minimum number of the given dimension
static KDNode *findMin(int dim, KDNode *leaf);

// private returns minimum KDNode in the vector
static KDNode *minOfPoints(const std::vector<KDNode *> &points, int dim);

static void findNN(const KDNode *node, const std::vector<int> &point, double &best_dist, std::shared_ptr<KDNode> &curr_best);
static double eucledian_distance(std::vector<int> point1, std::vector<int> point2);
 */