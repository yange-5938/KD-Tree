#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include "kd-tree.h"

// Constructor,
// points root to null.
// pass in the dimention
KDTree::KDTree(int dim)
    : DIM(dim)
{
    root = nullptr;
}

// insert a vector into the kd-tree
void KDTree::insert(std::vector<int> vec)
{
    if (root != nullptr)
        insert(vec, root);
    else
    {
        root = new KDNode;
        root->cuttingEdge = 0;
        root->vector = vec;
        root->left = nullptr;
        root->right = nullptr;
    }
}
// private method inserts a vector into the kd-tree
void KDTree::insert(std::vector<int> vec, KDNode *leaf)
{
    if (vec[leaf->cuttingEdge] < leaf->vector[leaf->cuttingEdge])
    {
        if (leaf->left != nullptr)
            insert(vec, leaf->left);
        else
        {
            leaf->left = new KDNode;
            leaf->left->vector = vec;
            leaf->left->cuttingEdge = (leaf->cuttingEdge + 1) % DIM;
            leaf->left->left = nullptr;  // Sets the left child of the child node to null
            leaf->left->right = nullptr; // Sets the right child of the child node to null
        }
    }
    else if (vec[leaf->cuttingEdge] >= leaf->vector[leaf->cuttingEdge])
    {
        if (leaf->right != nullptr)
            insert(vec, leaf->right);
        else
        {
            leaf->right = new KDNode;
            leaf->right->vector = vec;
            leaf->right->cuttingEdge = (leaf->cuttingEdge + 1) % DIM;
            leaf->right->left = nullptr;  // Sets the left child of the child node to null
            leaf->right->right = nullptr; // Sets the right child of the child node to null
        }
    }
}

// printing the tree in the terminal
void KDTree::printKDT()
{
    printKDT("", this->root, true);
}
// private method prints the kd-tree in terminal
void KDTree::printKDT(const std::string &prefix,
                      const KDNode *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├─l─" : "└─r─");

        // print the value of the node
        std::cout << "(" << node->vector.at(0) << " , " << node->vector.at(1)<< " , "  << ")" << std::endl;

        // enter the next tree level - left and right branch
        printKDT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printKDT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

// delete the node, which stores the exactly same vector
KDNode *KDTree::deleteNode(std::vector<int> point)
{
    return deleteNode(point, this->root);
}

// private method deletes the node, which stores the exactly same vector
KDNode *KDTree::deleteNode(std::vector<int> point, KDNode *leaf)
{
    if (leaf == nullptr)

        throw "point not found!";

    if (point == leaf->vector)
    {
        if (leaf->right != nullptr)
        {
            leaf->vector = findMin(leaf->cuttingEdge, leaf->right)->vector;
            leaf->right = deleteNode(leaf->vector, leaf->right);
        }
        else if (leaf->left != nullptr)
        {
            leaf->vector = findMin(leaf->cuttingEdge, leaf->left)->vector;
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

// private returns minimun KDNode in the vector
KDNode *KDTree::minOfPoints(std::vector<KDNode *> points, int dim)
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
KDNode *KDTree::findMin(int dim)
{
    return findMin(dim, root);
}

// private method returns the vector which has the minumun number of the given dimension
KDNode *KDTree::findMin(int dim, KDNode *leaf)
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

        return KDTree::minOfPoints({findMin(dim, leaf->right),
                                    findMin(dim, leaf->left),
                                    leaf},
                                   dim);
    }
}
