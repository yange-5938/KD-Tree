#ifndef HELPER_H
#define HELPER_H

#include <memory>
#include "kd-tree.h"


// this method creats a KD-Tree and it inserts all the points from the file to the tree
std::unique_ptr<KDTree> createKDTreeFromFile(std::string file_name, int dim);

// this method creats a KD-Tree and it inserts all the points from a vector
std::unique_ptr<KDTree> createKDTreeFromVectors(std::vector<std::vector<int>> points, int dim);

// this method returns vector of vectors of points
std::vector<std::vector<int>> createVectorFromFile(std::string filename, int dim);


#endif // HELPER_H