#include <iostream>
#include "modint.hpp"

using namespace std;

const static int mod = 1000000007;

ModInt<mod> fact[111111];
ModInt<mod> fact_inv[111111];

int comb(int n, int k) {
  int ans = (fact[n] * fact_inv[k] * fact_inv[n-k]).get();
  return ans;
}

int main() {
  ModInt<mod> x(1);
  fact[0] = x;
  fact_inv[0] = x;
  int n = 20;
  for(int i = 1; i < n; ++i){
    x *= i;
    fact[i] = x;
    fact_inv[i] = inv(x);
  }

  for(int i = 0; i < n;i ++) {
    cout << i << " " << fact[i] << endl;
  }
}
