#ifndef RMQ_HPP_
#define RMQ_HPP_

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>


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
  T query(int a, int b, int k, int l, int r){
    if(r <= a || b <= l) {
      return INT_MAX;
    }
    if(a <= l && r <= b) {
      return val[k];
    }else {
      T vl = query(a, b, k*2+1, l, (l+r)/2);
      T vr = query(a, b, k*2+2, (l+r)/2, r);
      return std::min(vl, vr);
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
  std::vector<T> val;

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
  T operator[](int idx){
    if(idx < 0 || n < idx) {
      throw "out of range";
    }
    return val[idx+nn-1];
  }

  /**
   * update the value so that rmq[i] = x 
   */
  void update(int i, T x){
    if(i < 0 || n < i) {
      throw "out of range";
    }
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
  T mn(int a, int b){
    if(a >= b) {
      throw "empty set";
    }
    if(a < 0 || n < b) {
      throw "out of range";
    }
    return query(a, b, 0, 0, nn);
  }  
};

#endif
