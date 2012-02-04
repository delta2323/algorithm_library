#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "msp.hpp"

using namespace std;

TEST(msp, line) {
  int n = 10;
  int inf = 1 << 30;
  vector<vector<int> > g(n, vector<int>(n));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      g[i][j] = inf;
    }
  }

  for(int i = 0; i < n-1; i++) {
    g[i][i+1] = 1;
  }
  ASSERT_EQ(n-1, msp(g));
}

TEST(msp, complete) {
  int n = 10;
  int inf = 1 << 31;
  vector<vector<int> > g(n, vector<int>(n));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      g[i][j] = i == j ? inf : 1;
    }
  }
  ASSERT_EQ(n-1, msp(g));
}
