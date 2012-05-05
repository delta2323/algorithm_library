#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <vector>

#include "lca.hpp"

using namespace std;

TEST(Trivial, lca) {
  int n = 1;
  LCA lca(n);
  vector<vector<int> > adj(n, vector<int>());
  lca.init(adj, 0);
  ASSERT_EQ(0, lca.query(0, 0));
}

class SmallTest : public ::testing::Test {
public:
  virtual void SetUp() {
    n = 3;
    root = 0;
    lca = new LCA(n);
    vector<vector<int> > adj(3, vector<int>());
    adj[root].push_back(1); adj[root].push_back(2);
    lca->init(adj, root);
  }
protected:
  int n;
  LCA* lca; 
  int root;
};

TEST_F(SmallTest, query1) {
  ASSERT_EQ(root, lca->query(0, 1));
}
TEST_F(SmallTest, query2) {
  ASSERT_EQ(root, lca->query(0, 2));
}
TEST_F(SmallTest, query3) {
  ASSERT_EQ(root, lca->query(1, 2));
}

class SmallTestChangeIdx1 : public ::testing::Test {
public:
  virtual void SetUp() {
    n = 3;
    root = 1;
    lca = new LCA(n);
    vector<vector<int> > adj(3, vector<int>());
    adj[root].push_back(0); adj[root].push_back(2);
    lca->init(adj, root);
  }
protected:
  int n;
  LCA* lca; 
  int root;
};

TEST_F(SmallTestChangeIdx1, query1) {
  lca->dump();
  ASSERT_EQ(root, lca->query(0, 1));
}
TEST_F(SmallTestChangeIdx1, query2) {
  ASSERT_EQ(root, lca->query(0, 2));
}
TEST_F(SmallTestChangeIdx1, query3) {
  ASSERT_EQ(root, lca->query(1, 2));
}

class SmallTestChangeIdx2 : public ::testing::Test {
public:
  virtual void SetUp() {
    n = 3;
    root = 2;
    lca = new LCA(n);
    vector<vector<int> > adj(3, vector<int>());
    adj[root].push_back(0); adj[root].push_back(1);
    lca->init(adj, root);
  }
protected:
  int n;
  LCA* lca;
  int root;
};

TEST_F(SmallTestChangeIdx2, query1) {
  ASSERT_EQ(root, lca->query(0, 1));
}
TEST_F(SmallTestChangeIdx2, query2) {
  ASSERT_EQ(root, lca->query(0, 2));
}
TEST_F(SmallTestChangeIdx2, query3) {
  ASSERT_EQ(root, lca->query(1, 2));
}

class TallTreeTest : public ::testing::TestWithParam<int> {
public:
  TallTreeTest(){}
  virtual void SetUp() {
    root = 0;
    lca = new LCA(n);
    vector<vector<int> > adj(10, vector<int>());
    for(int i = 1; i < n; ++i) {
      adj[0].push_back(i);
    }
    lca->init(adj, root);
  }
  const static int n = 10;
protected:
  int root;
  LCA* lca;
};

INSTANTIATE_TEST_CASE_P(TallTreeTestInstance,
                        TallTreeTest,
                        testing::Range(1, TallTreeTest::n));
TEST_P(TallTreeTest, value_parametrized_test_sample) {
  ASSERT_EQ(root, lca->query(root, GetParam()));
}
