#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include "../print.hpp"

using namespace std;

/**
 * @description : return the longest increasing sequence (LIS)
 * @param b : target sequence
 * @return  : length of the LIS of b
 * (table stores one of the LIS in b) 
 *
 * cost : O(n log n) where n is the length of b
 */

int lis(vector<int>& b){
  size_t n = b.size();
  vector<int > table(n,INT_MAX);
  for(int i = 0;i<n;i++){
    *lower_bound(table.begin(), table.end(), b[i]) = b[i];
  }
  print(table);
  return lower_bound(table.begin(), table.end(), INT_MAX) - table.begin();
}

int main(){
  srand((unsigned) time(NULL));
  int n = 10;
  vector<int > s(n);
  for(int i = 0;i<n;i++){
    s[i] = rand() % 10;
  }
  print(s);
  cout << lis(s) << endl;
  return 0;
}


