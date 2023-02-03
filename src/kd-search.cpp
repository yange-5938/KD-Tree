#include "cmath"

#include "kd-search.h"
#include "kd-tree.h"

std::vector<int> findNN(KDTree tree, const std::vector<int> &point)
{
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
