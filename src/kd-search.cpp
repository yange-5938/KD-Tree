#include "kd-search.h"
#include "iostream"
#include "limits"
#include "cmath"

KDNode* SearchStrategies::findMin(int dim, KDNode *leaf)
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

    return minOfPoints({findMin(dim, leaf->right),
                          findMin(dim, leaf->left),
                          leaf},
                         dim);
  }
}


KDNode *SearchStrategies::minOfPoints(const std::vector<KDNode *> &points, int dim)
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

std::vector<int> SearchStrategies::findMin(int dim, KDTree tree) {
  return this->findMin(dim, tree.root)->vector; //TODO: check full nullptr
}

std::vector<int> SearchStrategies::findKNN(KDTree tree, const std::vector<int> &point) {
  double inf = std::numeric_limits<double>::infinity();
  return this->findKNN(tree.root, point, inf, nullptr)->vector; // TODO: check for nullptr
}

KDNode *SearchStrategies::findKNN(KDNode *node, const std::vector<int> &point, double &best_dist, KDNode *curr_best) {
  if (!node) {
    return curr_best;
  }
  best_dist = std::min(best_dist, eucledian_distance(node->vector, point));
  auto cuttingEdge = node->cuttingEdge;
  char choice = 0;
  if (point[cuttingEdge] <= node->vector[cuttingEdge])
  {
    findKNN(node->left, point, best_dist, curr_best);
  }
  else
  {
    choice = 1;
    findKNN(node->right, point, best_dist, curr_best);
  }
  if (choice && ) {

  }
}

double SearchStrategies::eucledian_distance(std::vector<int> point1, std::vector<int> point2) {
  double sum = 0;
  auto el1 = point1.begin();
  auto el2 = point2.begin();
  while (el1 != point1.end())
  {
    sum += pow((*el2 - *el1), 2);
  }
  return sqrt(sum);
}
