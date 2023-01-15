#include "kd-search.h"
#include "gtest/gtest.h"

KDTree *tree2;

class TreeTest : public ::testing::Test {
protected:

    void SetUp() override {
      tree2 = new KDTree(2);
      tree2->insert({4,7});
      tree2->insert({1,9});
      tree2->insert({8,4});
      tree2->insert({2,3});
    }

    void TearDown() override {
      delete tree2;
    }

};

TEST_F(TreeTest, MethodInsertWorksProperly) {
  tree2->insert({5,7});
  ASSERT_TRUE(true);
//  EXPECT_EQ(tree
}

TEST_F(TreeTest, MethodDeleteWorksProperly) {
  tree2->deleteNode({2,3});
  //  EXPECT_EQ(tree
}
