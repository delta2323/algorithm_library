#include <iostream> 
#include <unionfind.hpp>

using namespace std;

int main () {
  UnionFind uf(10);
  uf.unite(1, 0);
  if(uf.same(0, 1)) {
    cout << "ok" << endl;
  }
}
