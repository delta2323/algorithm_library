#include <gtest/gtest.h>
#include "bit.hpp"

using namespace std;

TEST(bit, oridinal_usage1) {
  int n = 10;
  BIT<int >  bit(n);

  ASSERT_EQ(10, bit.size());

  for(int i = 0; i < n; i++){
    bit.add(i, i*10);
  }
  for(int i = 0; i < n; i++){
    ASSERT_EQ(i*(i-1)*5, bit.sum(i));
  }
}

TEST(bit, out_of_range) {
  int n = 10;
  BIT<int >  bit(n);

  ASSERT_THROW(bit.add(-1, 10000), const char*);
  for(int i = 0; i <= n; ++i) {
    ASSERT_NO_THROW(bit.add(i, 10000));
  }
  ASSERT_THROW(bit.add(11, 10000), const char*);

  ASSERT_THROW(bit.sum(-1), const char*);
  for(int i = 0; i <= n; ++i) {
    ASSERT_NO_THROW(bit.sum(i));
  }
  ASSERT_THROW(bit.sum(11), const char*);
}

TEST(bit, empty) {
  int n = 0;
  BIT<int >  bit(n);

  ASSERT_EQ(0, bit.size());
}

