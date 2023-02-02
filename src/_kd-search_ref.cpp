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
  return findMin(dim, tree.root)->vector; //TODO: check full nullptr
}

std::vector<int> SearchStrategies::findNN(KDTree tree, const std::vector<int> &point) {
  double inf = std::numeric_limits<double>::infinity();
  auto curr_best = std::make_shared<KDNode>();
  findNN(tree.root, point, inf, curr_best);
  return curr_best->vector;
}

void SearchStrategies::findNN(const KDNode *node, const std::vector<int> &point, double &best_dist, std::shared_ptr<KDNode>& curr_best) {
  if (!node) {
    return;
  }

  if (double dist = eucledian_distance(node->vector, point); dist < best_dist)
  {
    *curr_best = *node;
    best_dist = dist;
  }
  auto cuttingEdge = node->cuttingEdge;
  char choice = 0;
  auto el1 = point[cuttingEdge]; //TODO: use better descriptive names
  auto el2 = node->vector[cuttingEdge]; //TODO: use better descriptive names
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
    if (choice){
      findNN(node->left, point, best_dist, curr_best);
    }
    else
    {
      findNN(node->right, point, best_dist, curr_best);
    }
  }
}

double SearchStrategies::eucledian_distance(std::vector<int> point1, std::vector<int> point2) {
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
