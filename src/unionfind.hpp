#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include <vector>

class UnionFind{
public:
  UnionFind(int _n);
  int find(int x);
  void unite(int x, int y);
  bool same(int x, int y);
private:
  int n;
  std::vector<int> par;
  std::vector<int> rank;
};

#endif
