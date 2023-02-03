#include "cmath"

#include "../src/helper.h"
#include "../src/kd-tree.h"
#include "../src/kd-search.h"
#include <gtest/gtest.h>

/* TEST(treetest, KNN_search) {
  std::vector<std::vector<int>> points = {{8, 8, 3}, {10, 4, 16}, {9, 12, 24},{5,8,6},{2,5,1}};
  auto kdt = createKDTreeFromVectors(points,3);

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

TEST(algo_test, eucledian_distance)
{
  std::vector<int> va, vb, vc, vd, ve;
  double dx;
  va = vb = {1, 1, 1};
  vc = {0, 0, 0};
  vd = {1, 0, 0, 0};
  ve = {0, 1, 1, 0};
  dx = eucledian_distance(va, vb);
  EXPECT_EQ(dx, 0);
  dx = eucledian_distance(vb, vc);
  EXPECT_EQ(dx, sqrt(3));
  dx = eucledian_distance(ve, vd);
  EXPECT_EQ(dx, sqrt(3));
}

TEST(tree_test, find_min)
{
  // test for 3d tree
  std::vector<std::vector<int>> points = {{8, 8, 0}, {10, 1, 16}, {9, 12, 24}, {5, 8, 6}, {2, 5, 1}};
  auto kdt = createKDTreeFromVectors(points, 3);

  auto a = kdt->findMin(0)->vector;
  std::vector<int> b = {2, 5, 1};
  EXPECT_EQ(a, b);

  a = kdt->findMin(1)->vector;
  b = {10, 1, 16};
  EXPECT_EQ(a, b);

  a = kdt->findMin(2)->vector;
  b = {{8, 8, 0}};
  EXPECT_EQ(a, b);

  // test for 4d tree
  points = {
      {8, 128, 20, 1},
      {1, 10, 1, 16},
      {52, 9, 12, 24},
      {5, 424, 8, 6},
  };
  kdt = createKDTreeFromVectors(points, 4);

  a = kdt->findMin(0)->vector;
  b = {1, 10, 1, 16};
  EXPECT_EQ(a, b);

  a = kdt->findMin(1)->vector;
  b = {52, 9, 12, 24};
  EXPECT_EQ(a, b);

  a = kdt->findMin(2)->vector;
  b = {1, 10, 1, 16};
  EXPECT_EQ(a, b);

  a = kdt->findMin(3)->vector;
  b = {8, 128, 20, 1};
  EXPECT_EQ(a, b);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
