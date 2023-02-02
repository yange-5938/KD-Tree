#ifndef HELPER_H
#define HELPER_H

#include <memory>
#include "kd-tree.h"


// this method creats a KD-Tree and it inserts all the points from the file to the tree
std::unique_ptr<KDTree> createKDTreeFromFile(std::string file_name, int dim);

#endif // HELPER_H