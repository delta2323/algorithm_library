#include <iostream>
#include <vector>
#include <algorithm>

#include "scc.hpp"

using namespace std;

void SCC::get_scc_idx(vector<int>& scc_idx) {
  scc_idx = result2_;
}

void SCC::get_scc_list(vector<vector<int> >& scc_list) {
  scc_list = result_;
}

SCC::SCC(const vector<vector<int> >& adj) :
  n_(adj.size()),
  adj_(adj),
  labelled_(adj.size()),
  in_scc_(adj.size()),
  result2_(adj.size()) {
  rev_.resize(n_);
  for(size_t i = 0; i < adj.size(); ++i) {
    for(size_t j = 0; j < adj[i].size(); ++j) {
      rev_[adj[i][j]].push_back(i);
    }
  }
}

void SCC::execute() {
  result2_.clear(); result2_.resize(n_);

  for(int i = 0; i < n_; ++i) {
    if(!labelled_[i]) {
      dfs(i);
    }
  }

  reverse(post_order_.begin(), post_order_.end());

  int scc_idx = 0;
  for(int i = 0; i < n_; ++i) {
    if(!in_scc_[post_order_[i]]) {
      dfs2(post_order_[i], scc_idx);
      ++scc_idx;
    }
  }
}

void SCC::dfs(int now) {
  labelled_[now] = true;
  for(size_t i = 0; i < adj_[now].size(); ++i) {
    int next = adj_[now][i];
    if(!labelled_[next]) {
      dfs(next);
    }
  }
  post_order_.push_back(now);
}

void SCC::dfs2(int now, int scc_idx) {
  if(static_cast<int>(result_.size()) <= scc_idx) {
    result_.resize(scc_idx+1);
  }

  result_[scc_idx].push_back(now);
  result2_[now] = scc_idx;
  in_scc_[now] = true;

  for(size_t i = 0; i < rev_[now].size(); ++i) {
    int next = rev_[now][i];
    if(!in_scc_[next]) {
      dfs2(next, scc_idx);
    }
  }
}
