#include <gtest/gtest.h>
#include <cstdlib>
#include <sys/time.h>
#include <vector>
#include <algorithm>

#include "rmq.hpp"

using namespace std;

TEST(rmq, oridinal_usage1) {
  srand(time(NULL));

  int n = 10;
  RMQ<int> rmq(n);
  vector<int> v(n);
  for(int i = 0; i < n; i++){
    int val = rand();
    v[i] = val;
    rmq.update(i, val);
  }
  sort(v.begin(), v.end());
  ASSERT_EQ(rmq.mn(0, n), v[0]);
  ASSERT_EQ(rmq.size(), static_cast<size_t>(n));
}

TEST(rmq, usage_of_operator) {
  int n = 10;
  RMQ<int> rmq(n);
  rmq.update(5, 111);
  int a = rmq[5];
  ASSERT_EQ(a, 111);
}

TEST(rmq, update) {
  for(int n = 1; n < 1000; ++n) {
    RMQ<int> rmq(n);
    for(int idx = 0; idx < n; ++idx) {
      rmq.update(idx, idx*10);
      ASSERT_EQ(rmq[idx], idx*10);
    }
  }
}

TEST(rmq, minimum) {
  for(int n = 1; n < 100; ++n) {
    vector<int> v(n);
    RMQ<int> rmq(n);
    for(int i = 0; i < n; i++) {
      int val = rand();
      rmq.update(i, val);
      v[i] = val;
    }

    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
	if(i >= j) {
	  ASSERT_THROW(rmq.mn(i, j), const char*);
	}else {
	  vector<int>::const_iterator it = min_element(v.begin()+i, v.begin()+j);
	  ASSERT_EQ(rmq.mn(i, j), *it);
	}
      }
    }
  }
}