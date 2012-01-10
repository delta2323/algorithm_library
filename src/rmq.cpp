#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

/**
 * rmq processes the following qeries 
 * (1) update the value 
 * (2) return the minimum value of [a, b) 
 */


template<typename T>
class RMQ{
private:

  /**
   * val : n
   * the number of underlying sequence
   */
  int n;

  /**
   * val : nn
   * nn is the minimum value which satisfies the following conditions
   * (1) nn is some power of 2
   * (2) n <= nn;
   */
  int nn;

  /**
   * function : query
   * used in function mn below
   */
  int query(int a, int b, int k, int l,int r){
    if(r<= a || b<= l) return INT_MAX;
    if(a <= l && r <= b) return val[k];
    else{
      int vl = query(a,b,k*2+1, l, (l+r)/2);
      int vr = query(a,b,k*2+2, (l+r)/2, r);
      return min(vl, vr);
    }
  }

  /**
   * structure of val is as follows
   *  where val is the undermost sequence
   *           0
   *      1          2
   *    3   4     5     6
   *   7 8 9 10 11 12 13 14
   */
  vector<T> val;

public:
  RMQ(int _n) : n(_n){
    nn = 1;
    while(n > nn) nn *= 2;    
    val.resize(nn*2-1);
    for(size_t i = 0;i<val.size();i++){
      val[i] = INT_MAX;
    }
  }
  RMQ(size_t _n){RMQ((int) _n);}
  RMQ(){RMQ(0);}

  inline size_t size(){return n;}

  /**
   * return the value of underlying seq
   * in the example above
   * rmq[0+j] = val[7+j]
   */
  T operator[](size_t at){
    return val[at+nn-1];
  }

  /**
   * update the value so that rmq[i] = x 
   */
  void update(int i,int x){
    i += nn-1;
    val[i] = x;
    while(i > 0){
      i = (i-1)/2;
      val[i] = min(val[i*2+1], val[i*2+2]);
    }
  }

  /**
   * return the minimum value in rmq[a,b)
   */
  T mn(int a,int b){
    return query(a,b,0,0,nn);
  }  
};

int main(){
  int n;cin >>n;
  RMQ<int> rmq(n);
  for(int i = 0;i<n;i++){
    rmq.update(i, 100*cos(i));
  }
  
  while(1){
  for(int i = 0;i<n;i++){
    cout.width(3);
    cout << i << " ";
  }
  cout << endl;
  for(int i = 0;i<n;i++){
    cout.width(3);
    cout << rmq[i] << " ";
  }
  cout << endl;

  int r,l;
  cin >> l >> r;
  cout << rmq.mn(l,r) << endl;
  }
  return 0;

}
