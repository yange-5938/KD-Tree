#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

struct KDNode
{
    int cuttingEdge;
    std::vector<int> vector;
    KDNode *left;
    KDNode *right;
};

// Class of KD tree
class KDTree
{
private:
    // root 
    KDNode *root;
    
    void printKDT(int a); 
    KDNode *minOfPoints(std::vector<KDNode *> points, int dim);
    void printKDT(const std::string &prefix,
                  const KDNode *node, bool isLeft);
    void insert(std::vector<int> vec, KDNode *leaf);
    KDNode *findMin(int dim, KDNode *leaf);
    KDNode *deleteNode(std::vector<int> point, KDNode *leaf);

    friend class SearchStrategies;

public:

    const int DIM;
    // Constructor
    KDTree(int); 
    
    // default Constructor without passing dimension is not allow
    KDTree() = delete;
    void insert(std::vector<int> vec);

    // printing the tree in the terminal
    void printKDT(); 
    KDNode *findMin(int dim);
    KDNode *deleteNode(std::vector<int> point);
};

#endif // KD-TREEH