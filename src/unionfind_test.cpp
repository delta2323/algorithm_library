#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <vector>

#include "unionfind.hpp"

using namespace std;

const static int inf = 1 << 25;

TEST(unionfind, oridinal_usage1) {
  int n = 10;
  UnionFind uf(n);
  uf.unite(3, 7);
  uf.unite(7, 5);

  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      cout << "check :" << i << " " << j << endl;
      if((i == 3 && j == 5) || (i == 5 && j == 3) ||
	 (i == 3 && j == 7) || (i == 7 && j == 3) ||
	 (i == 5 && j == 7) || (i == 7 && j == 5) ||
	 (i == j)) {
	ASSERT_TRUE(uf.same(i, j));	
      }else {
	ASSERT_FALSE(uf.same(i, j));
      }
    }
  }
}

void Warshall_Floyd(const vector<vector<int> >& cost, vector<vector<int> > & ret) {
  int n = cost.size();
  vector<vector<int> > tmp(cost);

  cout << "WF" << endl;
  for(int i = 0; i < n; i ++) {
    for(int j = 0; j < n; j ++) {
      cout << tmp[i][j] << " ";
    }
    cout << endl;
  }

  for(int k = 0; k < n; ++k) {
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
	tmp[i][j] = min(tmp[i][j], tmp[i][k] + tmp[k][j]);
      }
    }
  }
  swap(tmp, ret);
}

bool connected(const vector<vector<int> >& g) {
  vector<vector<int> > cost;
  Warshall_Floyd(g, cost);

  int n = cost.size();
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      if(cost[i][j] == inf) {
	return false;
      }
    }
  }
  return true;
}

void generate_connected_graph(int n, vector<vector<int> >& ret) {
  vector<vector<int> > g(n, vector<int>(n, inf));
  for(int i = 0; i < n; ++i) {
    g[i][i] = 0;
  }

  for(int i = 0; i < n*n/10; ++i) {
    int from = rand() % n;
    int to = rand() % n;
    g[from][to] = g[to][from] = 1;
  }

  while(true) {
    if(connected(g)) {
      break;
    }

    int from = 0;
    int to = 0;
    while(true) {
      from = rand() % n;
      to = rand() % n;
      cout << "Candidate Edge: " << from << " " << to << endl;
      if(from == to) {
	continue;
      }
      if(g[from][to] == inf) {
	break;
      }
    }
    cout << "Add Edge: " << from << " " << to << endl;
    g[from][to] = g[to][from] = 1;
  }
  swap(ret, g);
}

void print(const vector<vector<int> >& g) {
  int n = g.size();
  for(int i = 0; i < n; i ++) {
    for(int j = 0; j < n; j ++) {
      cout << g[i][j] << " ";
    }
    cout << endl;
  }
}

TEST(unionfind, spanning_tree) {
  srand(time(NULL));
  int n = 20;
  vector<vector<int> > g;
  generate_connected_graph(n, g);

  cout << "Connected Graph" << endl;
  print(g);
  ASSERT_TRUE(connected(g));

  vector<vector<int> > spanning_tree(n, vector<int>(n, inf));;
  for(int i = 0; i < n; ++i) {
    spanning_tree[i][i] = 0;
  }

  UnionFind uf(n);
  vector<int> used(n);
  used[0] = 1;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      for(int k = 0; k < n; ++k) {
	if(g[j][k] != inf && !uf.same(j, k) && used[j] == 1) {
	  ASSERT_EQ(0, used[k]);
	  uf.unite(j, k);
	  used[k] = 1;
	  spanning_tree[j][k] = spanning_tree[k][j] = 1;
	}
      }
    }
  }

  cout << "Spanning Tree" << endl;
  print(spanning_tree);

  vector<vector<int> > cost;
  Warshall_Floyd(spanning_tree, cost);

  cout << "Cost" << endl;
  print(cost);

  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      cout << "check : " << i << " " << j << endl;
      ASSERT_TRUE(cost[i][j] != inf);
    }
  }
}
