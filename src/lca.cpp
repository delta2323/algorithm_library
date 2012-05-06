#include <vector>
#include <queue>

#include "lca.hpp"
#include "rmq.hpp"
#include "print.hpp"

using namespace std;

LCA::LCA(int n) : rmq(2*n-1){}

void LCA::init(const vector<vector<int> >& adj_list, int root) {
  n_ = adj_list.size();
  root_ = root;
  adj_ = adj_list;
  
  id2bfsid_.clear(); id2bfsid_.resize(n_, -1);
  bfsid2id_.clear();
  bfs();

  euler_.clear();
  id2euler_.clear(); id2euler_.resize(n_, -1);
  dfs(root);
}

void LCA::bfs() {
  queue<int> q;
  q.push(root_);
  while(!q.empty()) {
    int now = q.front(); q.pop();
    if(id2bfsid_[now] != -1) {
      continue;
    }
    id2bfsid_[now] = static_cast<int>(bfsid2id_.size());
    bfsid2id_.push_back(now);
    for(size_t i = 0; i < adj_[now].size(); ++i) {
      q.push(adj_[now][i]);
    }
  }
}

void LCA::dfs(int now) {
  id2euler_[now] = static_cast<int>(euler_.size());
  rmq.update(euler_.size(), id2bfsid_[now]);
  euler_.push_back(now);
  for(size_t i = 0; i < adj_[now].size(); ++i) {
    int next = adj_[now][i];
    if(id2euler_[next] != -1) {
      continue;
    }
    dfs(next);
    rmq.update(euler_.size(), id2bfsid_[now]);
    euler_.push_back(now);
  }
}

int LCA::query(int x, int y) {
  int euler_x = id2euler_[x];
  int euler_y = id2euler_[y];
  if(euler_x > euler_y) {
    swap(euler_x, euler_y);
  }
  int ret_bfsid = rmq.mn(euler_x, euler_y+1);
  return bfsid2id_[ret_bfsid];
}



void LCA::dump() {
  cout << "id2bfsid" << endl;
  print(id2bfsid_);
  cout << "bfsid2id" << endl;
  print(bfsid2id_);
  cout << "euler" << endl;
  print(euler_);
  cout << "id2euler" << endl;
  print(id2euler_);
}
