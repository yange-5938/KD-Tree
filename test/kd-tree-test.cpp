#include "../src/helper.h"
#include "../src/kd-tree.h"
#include <gtest/gtest.h>


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
