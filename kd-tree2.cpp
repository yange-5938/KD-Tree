#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

/* ## Sprint 1

Create a kd-tree data structure to store data with dimensionality k = 2, hence creating a 2D-tree. Optionally you can choose to go for k = 3 or k being variable.

### Definion of "done"

* Kd-tree can be constructed
* Points can be added and deleted
* Points can be read in from file */

const int DIM = 2;

// KDNode is a node or a leaf in KD-tree
// the vec is its value
// cuttingEdge is the x or y cutting edge that is currently using
struct KDNode
{
    int cuttingEdge;
    std::vector<int> vector;
    KDNode *left;
    KDNode *right;
};

// Class of KD tree
// insert and delete has a public and private function, it serves OOP purpose.
class KDTree
{

    KDNode* minOfPoints(std::vector<KDNode *> points, int dim)
    {
        KDNode *min_el = NULL;
        for (auto point : points)
        {
            if (min_el == NULL)
            {
                min_el = point;
            }
            else if (point != NULL)
            {
                if (point->vector[dim] < min_el->vector[dim])
                {
                    min_el = point;
                }
            }
        }
        return min_el;
    }

public:
    // Constructor
    KDTree()
    {
        root = NULL;
    }

    void insert(std::vector<int> vec)
    {
        if (root != NULL)
            insert(vec, root);
        else
        {
            root = new KDNode;
            root->cuttingEdge = 0;
            root->vector = vec;
            root->left = NULL;
            root->right = NULL;
        }
    }

    KDNode *findMin(int dim)
    {
        return findMin(dim, root);
    }

    KDNode *deleteNode(std::vector<int> point)
    {
        return deleteNode(point, this->root);
    }


    KDNode *deleteNode(std::vector<int> point, KDNode *leaf)
        {
            if (leaf == NULL)
                throw "point not found!";
            
            if (point == leaf->vector)
            {
                if (leaf->right != NULL)
                {
                    leaf->vector = findMin(leaf->cuttingEdge, leaf->right)->vector;
                    leaf->right = deleteNode(leaf->vector, leaf->right);
                }
                else if (leaf->left != NULL)
                {
                    leaf->vector = findMin(leaf->cuttingEdge, leaf->left)->vector;
                    leaf->right = deleteNode(leaf->vector, leaf->left);
                }
                else 
                {
                    leaf = NULL;
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

private:

    
    void insert(std::vector<int> vec, KDNode *leaf)
    {
        if (vec[leaf->cuttingEdge] < leaf->vector[leaf->cuttingEdge])
        {
            if (leaf->left != NULL)
                insert(vec, leaf->left);
            else
            {
                leaf->left = new KDNode;
                leaf->left->vector = vec;
                leaf->left->cuttingEdge = (leaf->cuttingEdge + 1) % DIM;
                leaf->left->left = NULL;  // Sets the left child of the child node to null
                leaf->left->right = NULL; // Sets the right child of the child node to null
            }
        }
        else if (vec[leaf->cuttingEdge] >= leaf->vector[leaf->cuttingEdge])
        {
            if (leaf->right != NULL)
                insert(vec, leaf->right);
            else
            {
                leaf->right = new KDNode;
                leaf->right->vector = vec;
                leaf->right->cuttingEdge = (leaf->cuttingEdge + 1) % DIM;
                leaf->right->left = NULL;  // Sets the left child of the child node to null
                leaf->right->right = NULL; // Sets the right child of the child node to null
            }
        }
    }

    KDNode *findMin(int dim, KDNode *leaf)
    {
        if (leaf == NULL)
            return NULL;

        if (dim == leaf->cuttingEdge)
        {
            if (leaf->left == NULL)
                return leaf;
            else
                return findMin(dim, leaf->left);
        }
        else
        {

            return KDTree::minOfPoints({findMin(dim, leaf->right), findMin(dim, leaf->left), leaf}, dim);
        }
    }
    
    // root of the tree
    KDNode *root;
};

void createFromFile(std::string file_name, KDTree *tree)
{
    std::string line;
    std::ifstream my_file(file_name);
    int x, y;
    while (std::getline(my_file, line))
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream line_stream(line);

        line_stream >> x >> y;
        tree->insert({x, y});
    }
}

int main()
{
    KDTree *kdt = new KDTree;
    createFromFile("input.csv", kdt);

    int dim = 0;
    auto x = kdt->findMin(dim);
    std::cout << "min Point on dimension " << dim <<": [" << x->vector[0] << "," << x->vector[1] << "]" << "\n";

    kdt->deleteNode({50,30});
    std::cout << kdt << "\n";
}
