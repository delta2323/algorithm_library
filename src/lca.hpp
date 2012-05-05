#ifndef LCA_HPP__
#define LCA_HPP__

#include <vector>

#include "rmq.hpp"

class LCA {
public:
  LCA(int n);
  void init(const std::vector<std::vector<int> > & adj_list, int root);
  int query(int x, int y);
  void dump();
private:
  void bfs();
  void dfs(int now);
  int n_;
  int root_;
  RMQ<int> rmq;
  std::vector<std::vector<int> > adj_;
  std::vector<int> id2bfsid_;
  std::vector<int> bfsid2id_;
  std::vector<int> euler_;
  std::vector<int> id2euler_;
};

#endif // LCA_HPP__
