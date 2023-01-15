#include "kd-search.h"
#include "gtest/gtest.h"

KDTree *tree;

class SearchStrategiesTest : public ::testing::Test {
protected:

    void SetUp() override {
      tree = new KDTree(2);
      tree->insert({4,7});
      tree->insert({1,9});
      tree->insert({8,4});
      tree->insert({2,3});
    }

    void TearDown() override {
      delete tree;
    }

};

TEST_F(SearchStrategiesTest, MethodfindMinGetsTheMinPointForEachDim) {
    SearchStrategies s;
    EXPECT_EQ(s.findMin(0, *tree), std::vector<int>({1,9}));
    EXPECT_EQ(s.findMin(1, *tree), std::vector<int>({2,3}));
}

TEST_F(SearchStrategiesTest, MethodfindNNFindNearestPoint) {
  SearchStrategies s;
  EXPECT_EQ(s.findNN(*tree, {2, 4}), std::vector<int>({2, 3}));
  EXPECT_EQ(s.findNN(*tree, {9, 5}), std::vector<int>({8, 4}));
}
