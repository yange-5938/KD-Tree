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

TEST(search_test, eucledian_distance)
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

TEST(search_test, findNN)
{
  std::vector<std::vector<int>> points = {{4, 7}, {1, 9}, {8, 4}, {2, 3}};
  auto kdt = createKDTreeFromVectors(points, 2);
  SearchStrategies s;
  EXPECT_EQ(s.findNN(*kdt, {2, 4}), std::vector<int>({2, 3}));
  EXPECT_EQ(s.findNN(*kdt, {9, 5}), std::vector<int>({8, 4}));
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
