#include "node.hpp"
#include "red_black_tree.hpp"
#include <gtest/gtest.h>

TEST(NodeToggleColorTest, RedBlack) {
  node<int> a(nullptr, nullptr, nullptr, false, 1);
  ASSERT_EQ(false, a.toggleColor());
  ASSERT_EQ(true, a.toggleColor());
  ASSERT_EQ(false, a.isBlack());
}

TEST(InsertTest, InsertFind) {
  vector<int> nums = {5, 4, 1, 3, 2, 6, 7, 8};
  red_black_tree<int> tree(nums);
  for(int n : nums) {
    ASSERT_NE(nullptr, tree.find(n));
  }
  int x = 9999;
  ASSERT_EQ(nullptr, tree.find(x));
}

TEST(InsertTest, InsertCorrectness) {
  vector<int> nums = {5, 4, 1, 3, 2, 6, 7, 8};
  red_black_tree<int> tree(nums);
  ASSERT_EQ(nums.size(), tree.size());

  ASSERT_EQ(tree.root->data, 4);
  ASSERT_EQ(tree.root->isRed, false);

  ASSERT_EQ(tree.root->left->data, 2);
  ASSERT_EQ(tree.root->left->isRed, false);

  ASSERT_EQ(tree.root->left->left->data, 1);
  ASSERT_EQ(tree.root->left->left->isRed, true);

  ASSERT_EQ(tree.root->left->right->data, 3);
  ASSERT_EQ(tree.root->left->right->isRed, true);

  ASSERT_EQ(tree.root->right->data, 6);
  ASSERT_EQ(tree.root->right->isRed, true);

  ASSERT_EQ(tree.root->right->left->data, 5);
  ASSERT_EQ(tree.root->right->left->isRed, false);

  ASSERT_EQ(tree.root->right->right->data, 7);
  ASSERT_EQ(tree.root->right->right->isRed, false);

  ASSERT_EQ(tree.root->right->right->right->data, 8);
  ASSERT_EQ(tree.root->right->right->right->isRed, true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
