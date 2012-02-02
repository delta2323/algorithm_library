#include <gtest/gtest.h>
#include <string>
#include "edit_distance.hpp"

using namespace std;

TEST(edit_distance, same) {
  string s = "aaaaa";
  string t = "aaaaa";
  ASSERT_EQ(EditDistance(s, t), 0);
}

TEST(edit_distance, completely_different) {
  string s = "aaaaa";
  string t = "bbbbb";
  ASSERT_EQ(EditDistance(s, t), 5);
}

TEST(edit_distance, empty) {
  string s = "aaaaa";
  string t = "";
  ASSERT_EQ(EditDistance(s, t), 5);
}

