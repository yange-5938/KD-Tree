#include "kd-tree.h"
#include "kd-search.h"
#include "helper.h"

int main()
{
    // creates kd-tree from file
    auto kdt = createKDTreeFromFile("../data/points.csv", 3);

    // print it to terminal
    kdt->printKDT();

    // print the minumun vector in each dimension
    auto x = kdt->findMin(0);
    auto y = kdt->findMin(1);
    auto z = kdt->findMin(2);
    std::cout << "min Point on dimension 0 is: [" << x->vector[0] << "," << x->vector[1] << "," << x->vector[2] << "]"
              << "\n";
    std::cout << "min Point on dimension 1 is: [" << y->vector[0] << "," << y->vector[1] << "," << y->vector[2] << "]"
              << "\n";
    std::cout << "min Point on dimension 1 is: [" << z->vector[0] << "," << z->vector[1] << "," << z->vector[2] << "]"
              << "\n";
    // delete a vector to demonstrate
    // we now delete a vector, namely {40,20,22}
    try
    {
        kdt->deleteNode({44, 20, 22});
    }
    catch (
        const char *msg)
    {
        std::cout << msg << "\n";
        return 1;
    }

    // print the tree again after the deletion
    kdt->printKDT();

    // run some KNN search
    SearchStrategies search;
    std::vector<int> point = {10, 20, 0};
    std::vector<int> NN = search.findNN(*kdt, point);
    point = {24, 21, 2};
    NN = search.findNN(*kdt, point);
}