#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

vector<vector<pair<int, int> > > g; //g[source][i] = (dest, cost)
vector<int> dist;
vector<int> backward;

void dijkstra(int s) {
  int n = g.size();
  vector<int> visited(n);
  dist.resize(n, -1);
  backward.resize(n, -1);
  dist[s] = 0;
  visited[s] = 1;
  priority_queue<pair<int, int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
  q.push(make_pair(0, s));
  while(!q.empty()) {
    int now = q.top().second;
    q.pop();
    if(visited[now] == 2) continue;
    visited[now] = 2;
    for(int i = 0; i < g[now].size(); i++) {
      int next = g[now][i].first;
      int dv = dist[now] + g[now][i].second;
      if(dv < dist[next] || dist[next] == -1) {
	dist[next] = dv;
	visited[next] = 1;
	q.push(make_pair(dist[next], next));
	backward[next] = now;
      }
    }
  }
}

int main() {
  int n = 10;
  g.clear();
  g.resize(n);
  for(int i = 0; i < n-1; i++) {
    g[i].push_back(make_pair(i+1, i));
    g[i+1].push_back(make_pair(i, i));
  }
  for(int i = 0; i < g.size(); i++) {
    for(int j = 0; j < g[i].size(); j++) {
      cout << i << "->" << g[i][j].first << ":" << g[i][j].second << endl;
    }
  }

  dijkstra(0);
  for(int i = 0; i < n; i++) {
    cout << dist[i] << " ";
  }
  cout << endl;

  for(int i = 0; i < backward.size(); i++) {
    cout << backward[i] << " ";
  }
  cout << endl;
}
