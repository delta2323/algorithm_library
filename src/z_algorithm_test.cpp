#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>
#include <sys/time.h>
#include "z_algorithm.hpp"

using namespace std;

TEST(z_alg, search_one_leftmost_hit) {
  string s = "aaaaaaaaaa";
  ZAlg z(s);
  int n = s.size();

  for(size_t i = 0; i < n; ++i) {
    ASSERT_EQ(n-i, z.get(i));
  }
}

TEST(z_alg, random_test) {
  string s;
  srand(time(NULL));
  int n = 1000;
  for(int i = 0; i < n; ++i) {
    s += 'a' + rand() % 4;
  }
  vector<int> expected(n);
  for(int i = 0; i < n; ++i) {
    int len = 0;
    for(int j = 0; i+j < n; ++j) {
      if(s[j] != s[i+j]) {
	break;
      }
      ++len;
    }
    expected[i] = len;
  }

  ZAlg z(s);
  for(size_t i = 0; i < n; ++i) {
    ASSERT_EQ(expected[i], z.get(i));
  }
}



