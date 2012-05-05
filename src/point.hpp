#ifndef POINT_HPP__
#define POINT_HPP__


// 2012/05/05 Kenta OONO
// This module works only when T = double

template <typename T>
struct Point2 {
  const static int kINVALID = -1;
  int id_;
  T x_;
  T y_;
  Point2(){}
  Point2(const Point2<T>& p);
  Point2(int id, T x, T y) : id_(id), x_(x), y_(y) {}
  Point2(T x, T y) : id_(kINVALID), x_(x), y_(y) {}
  Point2<T> operator+= (const Point2<T>& p);
  Point2<T> operator+ (const Point2<T>& p) const;
  Point2<T> operator-= (const Point2<T>& p);
  Point2<T> operator- (const Point2<T>& p) const;
  Point2<T> operator*= (T k);
  Point2<T> operator* (T k) const;
  T dot(const Point2<T>& p) const;
  T det(const Point2<T>& p) const;
  T dist2() const;
};

template <typename T>
bool comp_by_id(const Point2<T>& p, const Point2<T>& q);
template <typename T>
bool comp_by_coord(const Point2<T>& p, const Point2<T>& q);
template <typename T>
T dist2(const Point2<T>& p, const Point2<T>& q);

#include "point_impl.hpp"

#endif // POINT_HPP__
