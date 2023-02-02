#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include "kd-tree.h"

void KDTree::insert(const std::vector<int> &vec)
  {
    if (root != nullptr)
    {
      insert(vec, root);
    }
    else
    {
      root = new KDNode;
      root->cuttingEdge = 0;
      root->vector = vec;
      root->left = nullptr;
      root->right = nullptr;
    }
  }

std::unique_ptr<KDTree> KDTree::createKDTreeFromFile(std::string file_name, int dims)
  {
    auto tree = std::make_unique<KDTree>(dims);
    std::string line;
    std::ifstream my_file(file_name);
    int x, y;
    while (std::getline(my_file, line))
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream line_stream(line);

        line_stream >> x >> y;

        tree->insert({x,
                      y});
    }
    return tree;
  }

void KDTree::printKDT(const std::string &prefix, const KDNode *node, bool isLeft)
{
  if (node != nullptr)
  {
    std::cout << prefix;

    std::cout << (isLeft ? "├─l─" : "└─r─");

    // print the value of the node
    std::cout << "( " << node->vector.at(0);
    for (int i = 1; i < node->vector.size(); ++i)
    {
      std::cout << ", " << node->vector[i];
    }
    std::cout << " )" << "\n";

    // enter the next tree level - left and right branch
    printKDT(prefix + (isLeft ? "│   " : "    "), node->left, true);
    printKDT(prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}

void KDTree::insert(std::vector<int> vec, KDNode *leaf)
{
  if (vec[leaf->cuttingEdge] < leaf->vector[leaf->cuttingEdge])
  {
    if (leaf->left != nullptr)
    {
      insert(vec, leaf->left);
    }
    else
    {
      leaf->left = new KDNode;
      leaf->left->vector = vec;
      leaf->left->cuttingEdge = (leaf->cuttingEdge + 1) % this->DIM;
      leaf->left->left = nullptr;  // Sets the left child of the child node to null
      leaf->left->right = nullptr; // Sets the right child of the child node to null
    }
  }
  else if (vec[leaf->cuttingEdge] >= leaf->vector[leaf->cuttingEdge])
  {
    if (leaf->right != nullptr)
    {
      insert(vec, leaf->right);
    }
    else
    {
      leaf->right = new KDNode;
      leaf->right->vector = vec;
      leaf->right->cuttingEdge = (leaf->cuttingEdge + 1) % this->DIM;
      leaf->right->left = nullptr;  // Sets the left child of the child node to null
      leaf->right->right = nullptr; // Sets the right child of the child node to null
    }
  }
}

#include "kd-search.h"
class SearchStrategies;
KDNode *KDTree::deleteNode(std::vector<int> point, KDNode *leaf)
{
  if (leaf == nullptr)
  {
    throw "point not found!";
  }

  if (point == leaf->vector)
  {
    KDTree tree(this->DIM);
    tree.insert(leaf->vector);
    if (leaf->right != nullptr)
    {
      leaf->vector =  SearchStrategies::findMin(leaf->cuttingEdge, tree);
      leaf->right = deleteNode(leaf->vector, leaf->right);
    }
    else if (leaf->left != nullptr)
    {
      leaf->vector = SearchStrategies::findMin(leaf->cuttingEdge, tree);
      leaf->right = deleteNode(leaf->vector, leaf->left);
      leaf->left = nullptr;
    }
    else
    {
      leaf = nullptr;
    }
  }
  else if (point[leaf->cuttingEdge] < leaf->vector[leaf->cuttingEdge])
  {
    leaf->left = deleteNode(point, leaf->left);
  }
  else
  {
    leaf->right = deleteNode(point, leaf->right);
  }
  return leaf;
}