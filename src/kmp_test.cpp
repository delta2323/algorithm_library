#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>
#include <sys/time.h>
#include "kmp.hpp"

using namespace std;

TEST(kmp, oridinal_usage1) {
  string s = "ABCABCABCABC";
  string key = "ABC";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);

  vector<int> expected;
  expected.push_back(0);
  expected.push_back(3);
  expected.push_back(6);
  expected.push_back(9);
  ASSERT_EQ(expected, table);
}

TEST(kmp, oridinal_usage2) {
  string s = "AAAAA";
  string key = "AAA";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);

  vector<int> expected;
  expected.push_back(0);
  expected.push_back(1);
  expected.push_back(2);
  ASSERT_EQ(expected, table);
}

TEST(kmp, empty_string) {
  string s = "";
  string key = "ABC";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);
  ASSERT_EQ(vector<int>(), table);
}

TEST(kmp, empty_key) {
  string s = "AAAAAAAAAAAAAAAAAA";
  string key = "";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);
  ASSERT_EQ(vector<int>(), table);
}

TEST(kmp, longer_key) {
  string s = "AA";
  string key = "AAAAAAAAAAAAAAAAAAAAAAAA";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);
  ASSERT_EQ(vector<int>(), table);
}

TEST(kmp, empty_hit) {
  string s = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
  string key = "BBBBBBB";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);
  ASSERT_EQ(vector<int>(), table);
}

TEST(kmp, random_srting) {
  int n = 100000;
  string key("abcd");
  int m = key.size();

  string s;
  for(int i = 0; i < n; ++i) {
    s += 'a' + (rand() % m);
  }

  vector<int> table;
  KMP kmp(key);
  kmp.search(s, table);

  vector<int> expected;
  for(int i = 0; i+m < n; ++i) {
    bool matched = true;
    for(int j = 0; j < m; ++j) {
      if(s[i+j] != key[j]) {
	matched = false;
      }
    }
    if(matched) {
      expected.push_back(i);
    }
  }
  ASSERT_EQ(expected, table);
}

TEST(kmp, search_one) {
  string s = "aaaaaaaaaa";
  string key = "bbbb";
  KMP kmp(key);
  ASSERT_EQ(-1, kmp.search_one(s));
}

TEST(kmp, search_one_leftmost_hit) {
  string s = "bcabcabc";
  string key = "abc";
  KMP kmp(key);
  ASSERT_EQ(2, kmp.search_one(s));
}
