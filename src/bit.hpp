#ifndef BIT_HPP_
#define BIT_HPP_

#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

template<typename T>
class BIT{
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
  std::vector<T> val;

public:
  BIT(int _n) : n(_n){
    nn = 1;
    while(n > nn) nn *= 2;    
    val.resize(nn);
    for(size_t i = 0;i<val.size();i++){
      val[i] = 0;
    }
  }
  BIT(size_t _n){BIT((int) _n);}
  BIT(){BIT(0);}

  inline size_t size(){return n;}

  /**
   * return the partial sum in [0, i) of a
   * Note that internal data is 1-indexed,
   * whereas access from outside is required to be 0-indexed
   */
  T sum(int i){
    if(i < 0 || n < i) {
      throw "out of range";
    }
    T s = static_cast<T>(0);
    while(i > 0){
      s += val[i];
      i -= i&-i;
    }
    return s;
  }

  /**
   * add x to a[i] where a[i] is considering sequence
   * note that internal data is 1-index,
   * whereas access from outside is required to be 0-indexed
   */

  void add(int i, T x){
    if(i < 0 || n < i) {
      throw "out of range";
    }

    i++;
    while(i <= n){
      val[i] += x;
      i += i & -i; 
    }
  }

};

#endif
