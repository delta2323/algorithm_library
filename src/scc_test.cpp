#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <sys/time.h>
#include <vector>

#include "scc.hpp"
#include "unionfind.hpp"

using namespace std;

class CircularTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    n = 10;
    adj.clear(); adj.resize(n);
    for(int i = 0; i < n; ++i) {
      adj[i].push_back((i+1)%n);
    }
    scc = new SCC(adj);
    scc->execute();
  }
  virtual void TearDown() {}

protected:
  int n;
  vector<vector<int> > adj;
  SCC* scc;
};

TEST_F(CircularTest, scc_idx) {
  vector<int> actual;
  scc->get_scc_idx(actual);
  for(int i = 0; i < n; ++i) {
    ASSERT_EQ(0, actual[i]);
  }
}

TEST_F(CircularTest, scc_list) {
  vector<vector<int> > actual;
  scc->get_scc_list(actual);
  ASSERT_EQ(1, actual.size());  
  sort(actual[0].begin(), actual[0].end());
  for(int i = 0; i < n; ++i) {
    ASSERT_EQ(i, actual[0][i]);
  }
}

class NoEdgeTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    n = 10;
    adj.clear(); adj.resize(n);
    scc = new SCC(adj);
    scc->execute();
  }
  virtual void TearDown() {}
protected:
  int n;
  vector<vector<int> > adj;
  SCC* scc;
};

TEST_F(NoEdgeTest, scc_idx) {
  vector<int> actual;
  scc->get_scc_idx(actual);
  sort(actual.begin(), actual.end());
  ASSERT_EQ(n, actual.size());
  for(int i = 0; i < n; ++i) {
    ASSERT_EQ(i, actual[i]);
  }
}

TEST_F(NoEdgeTest, scc_list) {
  vector<vector<int> > actual;
  scc->get_scc_list(actual);
  sort(actual.begin(), actual.end());
  ASSERT_EQ(n, actual.size());
  for(int i = 0; i < n; ++i) {
    ASSERT_EQ(n, actual.size());
    ASSERT_EQ(i, actual[i][0]);
  }
}

TEST(SCC, allow_selfloop) {
}

TEST(SCC, allow_multiple_edge) {
}

class RandomTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    srand(100);
    n = 100;
    adj_list.clear(); adj_list.resize(n);
    adj_matrix.clear(); adj_matrix.resize(n, vector<bool>(n, false));

    CreateRandomGraph();
    CreateExpectedResult();

    scc = new SCC(adj_list);
    scc->execute();
  }

  virtual void TearDown() {}

protected:
  int n;
  vector<vector<int> > adj_list;
  vector<vector<bool> > adj_matrix;
  SCC* scc;
  UnionFind* uf;

private:
  void CreateRandomGraph();
  void CreateExpectedResult();
};

void RandomTest::CreateRandomGraph() {
  int prob = 1;
  for(int i = 0; i < n; ++i) {
    adj_matrix[i][i] = true;
    for(int j = 0; j < n; ++j) {
      if(rand() % 100 < prob) {
	adj_list[i].push_back(j);
	adj_matrix[i][j] = true;
      }
    }
  }
}

void RandomTest::CreateExpectedResult() {
  for(int k = 0; k < n; ++k) {
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
	adj_matrix[i][j] = adj_matrix[i][j] || (adj_matrix[i][k] && adj_matrix[k][j]);
      }
    }
  }

  uf = new UnionFind(n);
  for(int i = 0; i < n; ++i) {
    for(int j = i; j < n; ++j) {
      if(adj_matrix[i][j] && adj_matrix[j][i]) {
	uf->unite(i, j);
      }
    }
  }
}

TEST_F(RandomTest, scc_idx) {
  vector<int> actual;
  scc->get_scc_idx(actual);
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      ASSERT_EQ(uf->same(i, j), actual[i] == actual[j]);
    }
  }
}

TEST_F(RandomTest, scc_list) {
  vector<vector<int> > actual;
  scc->get_scc_list(actual);

  for(size_t i = 0; i < actual.size(); ++i) {
    for(size_t j = 0; j < actual[i].size(); ++j) {
      for(size_t k = j+1; k < actual[i].size(); ++k) {
	ASSERT_TRUE(uf->same(actual[i][j], actual[i][k]));
      }
    }
  }
  cout << "scc size " << actual.size() << endl;
}



