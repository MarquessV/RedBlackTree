#include "red_black_tree.hpp"
#include <gtest/gtest.h>

TEST(InsertTest, InsertFind) {
  vector<int> nums = {5, 4, 1, 3, 2, 6, 7, 8};
  red_black_tree<int> tree(nums);
  for(int n : nums) {
    ASSERT_NE(false, tree.find(n));
  }
  int x = 9999;
  ASSERT_EQ(false, tree.find(x));
}

TEST(InsertTest, InsertCorrectness) {
  vector<int> nums = {5, 4, 1, 3, 2, 6, 7, 8};
  red_black_tree<int> tree;
  vector<pair<int, bool>> verify0 = { {5, true} };
  vector<pair<int, bool>> verify1 = { {5, true}, {4, false} };
  vector<pair<int, bool>> verify2 = { {4, true}, {1, false}, {5, false} };
  vector<pair<int, bool>> verify3 = { {4, true}, {1, true}, {3, false}, {5, true} };
  vector<pair<int, bool>> verify4 = { {4, true}, {2, true}, {1, false}, {3, false}, {5, true} };
  vector<pair<int, bool>> verify5 = { {4, true}, {2, true}, {1, false}, {3, false}, {5, true}, {6, false} };
  vector<pair<int, bool>> verify6 = { {4, true}, {2, true}, {1, false}, {3, false}, {6, true}, {5, false}, {7, false} };
  vector<pair<int, bool>> verify7 = { {4, true}, {2, true}, {1, false}, {3, false}, {6, false}, {5, true}, {7, true}, {8, false} };
  vector<pair<int, bool>> dump;
  tree.insert(nums[0]);
  ASSERT_EQ(tree.height(), 0);
  dump = tree.dump();
  ASSERT_EQ(verify0.size(), dump.size());
  ASSERT_EQ(verify0[0], dump[0]);

  tree.insert(nums[1]);
  ASSERT_EQ(tree.height(), 1);
  dump = tree.dump();
  ASSERT_EQ(verify1.size(), dump.size());
  for(int i = 0; i < 2; i++) {
    ASSERT_EQ(verify1[i], dump[i]);
  }

  tree.insert(nums[2]);
  ASSERT_EQ(tree.height(), 1);
  dump = tree.dump();
  ASSERT_EQ(verify2.size(), dump.size());
  for(int i = 0; i < 3; i++) {
    ASSERT_EQ(verify2[i], dump[i]);
  }

  tree.insert(nums[3]);
  ASSERT_EQ(tree.height(), 2);
  dump = tree.dump();
  ASSERT_EQ(verify3.size(), dump.size());
  for(int i = 0; i < 4; i++) {
    ASSERT_EQ(verify3[i], dump[i]);
  }

  tree.insert(nums[4]);
  ASSERT_EQ(tree.height(), 2);
  dump = tree.dump();
  ASSERT_EQ(verify4.size(), dump.size());
  for(int i = 0; i < 5; i++) {
    ASSERT_EQ(verify4[i], dump[i]);
  }

  tree.insert(nums[5]);
  ASSERT_EQ(tree.height(), 2);
  dump = tree.dump();
  ASSERT_EQ(verify5.size(), dump.size());
  for(int i = 0; i < 6; i++) {
    ASSERT_EQ(verify5[i], dump[i]);
  }

  tree.insert(nums[6]);
  ASSERT_EQ(tree.height(), 2);
  dump = tree.dump();
  ASSERT_EQ(verify6.size(), dump.size());
  for(int i = 0; i < 7; i++) {
    ASSERT_EQ(verify6[i], dump[i]);
  }

  tree.insert(nums[7]);
  ASSERT_EQ(tree.height(), 3);
  dump = tree.dump();
  ASSERT_EQ(verify7.size(), dump.size());
  for(int i = 0; i < 8; i++) {
    ASSERT_EQ(verify7[i], dump[i]);
  }
  /*
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
  */
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
