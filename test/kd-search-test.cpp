
#include "../src/helper.h"
#include "../src/kd-tree.h"
#include "../src/kd-search.h"
#include <gtest/gtest.h>

/* 
TEST(treetest, KNN_search) {
  std::vector<std::vector<int>> points = {{1, 2, 3}, {3, 2, 1}, {0, 1, 2}};
  auto root_point = points.front();

  // build the kd tree
  std::shared_ptr<Node> root = std::make_shared<Node>(root_point);
  KD_Tree kd_tree = KD_Tree(root);
  for (auto const &pt : points) {
    kd_tree.kd_insert(root, pt);
  }
  std::vector<int> a = kd_tree.KNN_point({1, 2, 2});
  std::vector<int> b = {1, 2, 3};
  GTEST_ASSERT_EQ(a, b);
} */

TEST(treetest, find_min) {
  std::vector<std::vector<int>> points = {{8, 8, 3}, {10, 4, 16}, {9, 12, 24},{5,8,6},{2,5,1}};
  auto kdt = createKDTreeFromVectors(points,3);

  auto a = kdt->findMin(0)->vector;
  std::vector<int> b = {2, 5, 1};
  std::cout<<"[ Message  ] This is the KD-Tree for test:"<<std::endl;
  kdt->printKDT();
  GTEST_ASSERT_EQ(a, b);
  //ASSERT_EQ(2,3);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
