#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

#include "dijkstra.hpp"

using namespace std;

const int Dijkstra::UNREACHABLE = std::numeric_limits<int>::max();

void Dijkstra::execute(const vector<vector<pair<int, int> > >& adj,
		       int start,
		       vector<int>& dist,
		       vector<int>& backward) {
  int n = adj.size();
  vector<int> visited(n);
  dist.clear(); dist.resize(n, UNREACHABLE);
  backward.clear(); backward.resize(n, -1);
  dist[start] = 0;
  visited[start] = 1;
  priority_queue<pair<int, int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
  q.push(make_pair(0, start));
  while(!q.empty()) {
    int now = q.top().second;
    q.pop();
    if(visited[now] == 2) continue;
    visited[now] = 2;
    for(size_t i = 0; i < adj[now].size(); i++) {
      int next = adj[now][i].first;
      int dv = dist[now] + adj[now][i].second;
      if(dist[next] == UNREACHABLE || dv < dist[next]) {
	dist[next] = dv;
	visited[next] = 1;
	q.push(make_pair(dist[next], next));
	backward[next] = now;
      }
    }
  }
}
