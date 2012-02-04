#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const static int INF = 1<<30;

int msp(vector<vector<int> > g) {
  int ret = 0;
  int n = g.size();
  vector<int> used(n);
  used[0] = 1;
  for(int i = 1; i < n; i++) {
    int mincost = INF;
    int minidx = 0;
    for(int j = 0; j < n; j++) {
      if(used[j] == 0) {
	continue;
      }

      for(int k = 0; k < n; k++) {
	if(j == k) {
	  continue;
	}
	if(used[k] == 1) {
	  continue;
	}
	if(mincost > g[j][k]) {
	  mincost = g[j][k];
	  minidx = k;
	}
      }
    }
    ret += mincost;
    used[minidx] = 1;
  }
  return ret;
}

/*
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
*/
