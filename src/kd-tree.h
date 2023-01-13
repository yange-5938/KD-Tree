#include <memory>
#include "iostream"
#include "vector"
#pragma once

class KDTree;

// KDNode is a node or a leaf in KD-tree
// the vec is its value
// cuttingEdge is the x or y cutting edge that is currently using
class KDNode
{
public:
    static KDNode *minOfPoints(const std::vector<KDNode *> &points, int dim);
    std::vector<int> vector;
private:
    friend class KDTree;
    friend class SearchStrategies;
    int cuttingEdge;
    KDNode *left;
    KDNode *right;
};

// Class of KD tree
// insert and delete has a public and private function, it serves OOP purpose.
class KDTree
{

    // public methods are for external use, it hides implementation details.
public:
    int DIM;
    // Constructor, points root to null.
    KDTree(int dims)
    {
      root = nullptr;
      DIM = dims;
    }

    // insert a vector into the kd-tree
    void insert(const std::vector<int> &vec);

    // printing the tree in the terminal
    void printKDT()
    {
      printKDT("", this->root, true);
    }

    // delete the node, which stores the exactly same vector
    KDNode *deleteNode(std::vector<int> point)
    {
      return deleteNode(point, this->root);
    }

    // this method creats a KD-Tree and it inserts all the points from the file to the tree
    static std::unique_ptr<KDTree> createKDTreeFromFile(std::string file_name, int dims);

private:
    // root of the tree
    KDNode *root;

    friend class SearchStrategies;

    // private method prints the kd-tree in terminal
    void printKDT(const std::string &prefix,
                  const KDNode *node, bool isLeft);

    // private method inserts a vector into the kd-tree
    void insert(std::vector<int> vec, KDNode *leaf);

    // private method deletes the node, which stores the exactly same vector
    KDNode *deleteNode(std::vector<int> point, KDNode *leaf);

};
