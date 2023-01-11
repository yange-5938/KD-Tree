#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

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

    // public method for printing the tree
    // eg.
    // ├──(30 , 40)
    // │   ├──(5 , 25)
    // │   │   ├──(10 , 12)
    // │   │   └──(2 , 30)
    // │   └──(70 , 70)
    // │       ├──(50 , 30)
    // │       └──(35 , 100)
    void printKDT(){
        printKDT("", this->root, true);
    }

    KDNode *findMin(int dim)
    {
        return findMin(dim, root);
    }

    KDNode *deleteNode(std::vector<int> point)
    {
        return deleteNode(point, this->root);
    }

        
    

private:

    // this method print the kd-tree in terminal
    void printKDT(const std::string& prefix, const KDNode* node, bool isLeft){
    if (node != nullptr){
        std::cout << prefix;
        
        std::cout << (isLeft ? "├─l─" : "└─r─");

        // print the value of the node
        std::cout << "(" << node->vector.at(0) << " , "<< node->vector.at(1) << ")"<< std::endl;

        // enter the next tree level - left and right branch
        printKDT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printKDT( prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }


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

        KDNode *deleteNode(std::vector<int> point, KDNode *leaf)
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
    
    // root of the tree
    KDNode *root;
};

// this method creats a KD-Tree and it inserts all the points from the file to the tree
KDTree* createKDTreeFromFile(std::string file_name)
{
    KDTree *tree = new KDTree;
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
    return tree;
}



int main()
{
    KDTree* kdt = createKDTreeFromFile("input.csv");
    
    kdt->printKDT();

    auto x = kdt->findMin(0);
    auto y = kdt->findMin(1);
    std::cout << "min Point on dimension 0 is: [" << x->vector[0] << "," << x->vector[1] << "]" << "\n";
    std::cout << "min Point on dimension 1 is: [" << y->vector[0] << "," << y->vector[1] << "]" << "\n";

    std::cout << "now we demonstrate the delete node function, type in a 2d-vector (eg. 2 and then 3)to delete: \n";
    std::cout << "type the first cordinate: \n";
    int first;
    std::cin >> first;

    std::cout << "now type the second cordinate: \n";
    int second;
    std::cin >> second;
    try{
        kdt->deleteNode({first,second});
    } catch (
        const char* msg
    ){
        std::cout << msg << "\n"; 
        return 1;
    }
    
    kdt->printKDT(); 
    
}
