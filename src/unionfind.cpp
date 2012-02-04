#include <vector>
#include "unionfind.hpp"

using namespace std;

UnionFind::UnionFind(int _n):n(_n){
  par.resize(n);
  for(int i = 0;i<n;i++){
    par[i] = i;
  }
  rank.resize(n, 0);
}

int UnionFind::find(int x){
  if(par[x] == x){
    return x;
  }else{
    return par[x] = find(par[x]);
  }
}

void UnionFind::unite(int x, int y){
  x = find(x);
  y = find(y);
  if(x == y) return ;
  if(rank[x] < rank[y]){
    par[x] = y;
  }else{
    par[y] = x;
  }
  if(rank[x] == rank[y]) rank[x]++;
}

bool UnionFind::same(int x, int y){
  return find(x) == find(y);
}
