#include "kd-search.h"
#include "gtest/gtest.h"

KDTree *tree;

class TreeTest : public ::testing::Test {
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

TEST_F(TreeTest, MethodInsertWorksProperly) {
  tree->insert({5,7});
//  EXPECT_EQ(tree
}

TEST_F(TreeTest, MethodDeleteWorksProperly) {
  tree->deleteNode({2,3});
  //  EXPECT_EQ(tree
}
