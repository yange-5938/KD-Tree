#include "iostream"
#include "kd-search.h"

int main()
{
  std::cout << "hello world" << "\n";
  KDTree tree{3};
  tree.insert({7,6,8});
  tree.insert({1,2,3});
  tree.deleteNode({1,2,3});
  tree.printKDT();
//  SearchStrategies::findMin()
}