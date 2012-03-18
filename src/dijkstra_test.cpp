#include <gtest/gtest.h>
#include <cstdlib>
#include <sys/time.h>
#include <vector>
#include <utility>
#include <algorithm>

#include "dijkstra.hpp"

using namespace std;

TEST(dijkstra, line_graph) {
  int n = 10;
  vector<vector<pair<int, int> > > adj(n);
  for(int i = 0; i < n-1; i++) {
    adj[i].push_back(make_pair(i+1, 1));
    adj[i+1].push_back(make_pair(i, 1));
  }

  vector<int> dist, backward;

  Dijkstra d;
  d.execute(adj, 0, dist, backward);

  for(size_t i = 0; i < dist.size(); ++i) {
    ASSERT_EQ(i, dist[i]);
    ASSERT_EQ(i-1, backward[i]);
  }
}

TEST(dijkstra, without_edge) {
  int n = 10;
  vector<vector<pair<int, int> > > adj(n);
  vector<int> dist, backward;

  Dijkstra d;
  for(int start = 0; start < n; ++start) {
    d.execute(adj, start, dist, backward);
    for(size_t i = 0; i < dist.size(); ++i) {
      int cost = start==(int)i ? 0 : Dijkstra::UNREACHABLE;
      ASSERT_EQ(cost, dist[i]);
      ASSERT_EQ(-1, backward[i]);
    }
  }
}

TEST(dijkstra, complete_graph) {
  int n = 10;
  vector<vector<pair<int, int> > > adj(n);
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      adj[i].push_back(make_pair(j, 1));
    }
  }

  vector<int> dist, backward;

  Dijkstra d;
  for(int start = 0; start < n; ++start) {
    d.execute(adj, start, dist, backward);
    for(size_t i = 0; i < dist.size(); ++i) {
      cout << "start=" << start << ", i=" <<i << endl;
      int cost = start==(int)i ? 0 : 1;
      int back = start==(int)i ? -1 : start;
      ASSERT_EQ(cost, dist[i]);
      ASSERT_EQ(back, backward[i]);
    }
  }
}
