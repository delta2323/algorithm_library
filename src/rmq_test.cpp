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

TEST(rmq, double_case_update) {
  for(int n = 1; n < 1000; ++n) {
    RMQ<double> rmq(n);
    for(int idx = 0; idx < n; ++idx) {
      rmq.update(idx, (double)(idx*10)+0.5);
    }
    for(int idx = 0; idx < n; ++idx) {
      ASSERT_EQ((double)(idx*10)+0.5, rmq[idx]);
    }
 }
}

TEST(rmq, failed_case) {
  int n = 2;
  RMQ<double> rmq(n);
  for(int idx = 0; idx < n; ++idx) {
    rmq.update(idx, (double)(idx*10)+0.5);
  }
  int one = 1;
  ASSERT_DOUBLE_EQ((double)((one-1)*10)+0.5, rmq.mn(0, one));
}

TEST(rmq, empty_set) {
  for(int n = 1; n < 1000; ++n) {
    RMQ<double> rmq(n);
    for(int idx = 0; idx < n; ++idx) {
      rmq.update(idx, (double)(idx*10)+0.5);
    }

    for(int idx = 0; idx < n; ++idx) {
      ASSERT_THROW(rmq.mn(idx, idx), const char*);
    }
  }  
}

TEST(rmq, double_case_mn) {
  for(int n = 1; n < 1000; ++n) {
    RMQ<double> rmq(n);
    for(int idx = 0; idx < n; ++idx) {
      rmq.update(idx, (double)(idx*10)+0.5);
    }

    for(int idx = 1; idx <= n; ++idx) {
      ASSERT_DOUBLE_EQ(0.5, rmq.mn(0, idx));
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

TEST(rmq, vector_constructor) {
  int n = 10;
  vector<int> v(n);
  for(size_t i = 0; i < n; ++i)  {
    v[i] = i*(n-i);
  }
  ASSERT_NO_THROW(RMQ<int> rmq(v));
}    

TEST(rmq, vector_constructor2) {
  int n = 10;
  vector<int> v(n);
  for(size_t i = 0; i < n; ++i)  {
    v[i] = -i*(n-i);
  }
  cout << "here1" << endl;
  RMQ<int> rmq(v);
  cout << "here2" << endl;
  for(int i = 0; i < n/2; ++i) {
    ASSERT_EQ(rmq.mn(0, i+1), -i*(n-i));
  }
  cout << "here3" << endl;
  for(int i = n/2; i < n; ++i) {
    ASSERT_EQ(rmq.mn(0, i+1), -(n/2)*(n-(n/2)));
  }
}
