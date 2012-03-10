#ifndef RMQ_HPP_
#define RMQ_HPP_

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

template<typename T>
class Segment {
public:
  T sum;
  T range_min;
  T left_min;
  T right_min;
  T mn;
  Segment(): sum(0),
	     range_min(std::numeric_limits<T>::max()),
	     left_min(std::numeric_limits<T>::max()),
	     right_min(std::numeric_limits<T>::max()),
	     mn(std::numeric_limits<T>::max()){}
  Segment(T x) : sum(x), range_min(x), left_min(x), right_min(x), mn(x){}
  Segment<T> operator=(const T& x);
  Segment<T> operator+=(const Segment<T>& b);
private:
  T add(T a, T b);
  void Swap(Segment<T>& tmp);
};
  
template <typename T>
Segment<T> Segment<T>::operator=(const T& x) {
  sum = x;
  range_min = x;
  left_min = x;
  right_min = x;
  mn = x;
  return *this;
}

template <typename T>
void Segment<T>::Swap(Segment<T>& a) {
  swap(sum, a.sum);
  swap(range_min, a.range_min);
  swap(left_min, a.left_min);
  swap(right_min, a.right_min);
  swap(mn, a.mn);
}

template <typename T>
T Segment<T>::add(T a, T b) {
  T ret;
  if(a == std::numeric_limits<T>::max() || b == std::numeric_limits<T>::max()) {
    ret = std::numeric_limits<T>::max();
  }else {
    ret = a + b;
  }
  return ret;
}

// This operator is inspired by this code.
// http://www.codeforces.com/contest/150/submission/1193366
template <typename T>
Segment<T> Segment<T>::operator+=(const Segment<T>& b) {
  Segment<T> tmp(*this);
  tmp.sum = this->sum + b.sum;
  tmp.range_min = min(min(this->range_min, b.range_min), this->right_min+b.left_min);
  tmp.left_min = min(this->left_min, add(this->sum, b.left_min));
  tmp.right_min = min(add(this->right_min, b.sum), b.right_min);
  tmp.mn = min(this->mn, b.mn);
  Swap(tmp);
  return *this;
}

template <typename T>
Segment<T> operator+(const Segment<T>& a, const Segment<T>& b) {
  Segment<T> ret(a);
  ret += b;
  return ret;
}

/**
 * rmq processes the following qeries 
 * (1) update the value 
 * (2) return the minimum value of [a, b) 
 */
template<typename T>
class RMQ {
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
  Segment<T> query(int a, int b, int k, int l, int r){
    if(r <= a || b <= l) {
      return Segment<T>();
    }
    if(a <= l && r <= b) {
      return val[k];
    }else {
      Segment<T> vl = query(a, b, k*2+1, l, (l+r)/2);
      Segment<T> vr = query(a, b, k*2+2, (l+r)/2, r);
      return vl+vr;
    }
  }

  bool bound_check(int a, int b) {
    if(a >= b) {
      return false;
    }
    if(a < 0 || n < b) {
      return false;
    }
    return true;
  }
  /**
   * structure of val is as follows
   *  where val is the undermost sequence
   *           0
   *      1          2
   *    3   4     5     6
   *   7 8 9 10 11 12 13 14
   */
  std::vector<Segment<T> > val;

public:
  RMQ(int _n) : n(_n){
    nn = 1;
    while(n > nn) nn *= 2;
    val.resize(nn*2-1);
    for(size_t i = 0; i < val.size(); ++i){
      val[i] = (std::numeric_limits<T>::max());
    }
  }
  RMQ(){}
  RMQ(const std::vector<T>& v) {
    n = static_cast<T>(v.size());
    nn = 1;
    while(n > nn) nn *= 2;
    val.resize(nn*2-1);
    for(size_t i = 0; i < val.size(); ++i){
      val[i] = (std::numeric_limits<T>::max());
    }
    for(size_t i = 0; i < v.size(); ++i) {
      update(i, v[i]);
    }
  }

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
    return val[idx+nn-1].mn;
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
      val[i] = val[i*2+1] + val[i*2+2];
    }
  }

  /**
   * return the minimum value in rmq[a,b)
   */
  T mn(int a, int b){
    if(!bound_check(a, b)) {
      throw "invalid range";
    }
    return query(a, b, 0, 0, nn).mn;
  }

  /**
   * return min_{a<=i<j<b} sum[i,j)
   */
  T range_min(int a, int b){
    if(!bound_check(a, b)) {
      throw "invalid range";
    }
    return query(a, b, 0, 0, nn).range_min;
  }

  /**
   * return sum[a,b)
   */
  T sum(int a, int b){
    if(!bound_check(a, b)) {
      return T();
    }
    return query(a, b, 0, 0, nn).sum;
  }
};

#endif
