#include "node.hpp"
#include <gtest/gtest.h>

TEST(NodeToggleColorTest, RedBlack) {
  node<int> a(nullptr, nullptr, nullptr, false, 1);
  ASSERT_EQ(true, a.toggleColor());
  ASSERT_EQ(false, a.toggleColor());
  ASSERT_EQ(true, a.isBlack());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
