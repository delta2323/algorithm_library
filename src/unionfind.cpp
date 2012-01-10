#include <iostream>
#include <vector>

using namespace std;

class UnionFind{
public:
  UnionFind(int _n):n(_n){
    par.resize(n);
    for(int i = 0;i<n;i++){
      par[i] = i;
    }
    rank.resize(n, 0);
  }

  int find(int x){
    if(par[x] == x){
      return x;
    }else{
      return par[x] = find(par[x]);
    }
  }

  void unite(int x, int y){
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
  bool same(int x, int y){
    return find(x) == find(y);
  }

private:
  int n;
  vector<int> par;
  vector<int> rank;

};


int main(){
  UnionFind uf(10);
  uf.unite(3, 7);
  uf.unite(7, 5);
  if(uf.same(3,5)){
    cout << "ok " << endl;
  }
}
