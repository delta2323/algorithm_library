#ifndef CONVEX_POLYTOPE_IMPL_HPP__
#define CONVEX_POLYTOPE_IMPL_HPP__

#include "line.hpp"
#include "approx.hpp"

template <typename T>
ConvexPolytope<T>::ConvexPolytope(const std::vector<Point2<T> >& ps) : ps_(ps), diameter_(kINVALID){}

template <typename T>
void ConvexPolytope<T>::convex_hull() {
  std::vector<Point2<T> > tmp(ps_.size()*2);
  std::sort(ps_.begin(), ps_.end(), comp_by_coord<T>);
  int k = 0;
  size_t n = ps_.size();
  for(size_t i = 0; i < n; ++i) {
    while(k > 1 && (tmp[k-1]-tmp[k-2]).det(ps_[i]-tmp[k-1]) <= 0) {
      --k;
    }
    tmp[k++] = ps_[i];
  }

  for(int i = static_cast<int>(n)-2, t = k; i >= 0; --i) {
    while(k > t && (tmp[k-1]-tmp[k-2]).det(ps_[i]-tmp[k-1]) <= 0) {
      --k;
    }
    tmp[k++] = ps_[i];
  }

  tmp.resize(k-1);
  swap(tmp, convex_hull_);
}

template <typename T>
void ConvexPolytope<T>::get_convex_hull(std::vector<Point2<T> >& ret) {
  if(convex_hull_.empty()) {
    convex_hull();
  }
  ret = convex_hull_;
}

template <typename T>
double ConvexPolytope<T>::diameter() {
  if(convex_hull_.empty()) {
    convex_hull();
    diameter_ = calc_diameter();
  }else if (!is_already_calc_diameter()) {
    diameter_ = calc_diameter();
  }
  return diameter_;
}

template <typename T>
bool ConvexPolytope<T>::is_already_calc_diameter() const {
  return diameter_ != kINVALID;
}

template <typename T>
double ConvexPolytope<T>::calc_diameter() const {
  size_t m = convex_hull_.size();

  size_t farest1_start = 0;
  size_t farest2_start = 0;
  {
    for(size_t i = 0; i < m; ++i) {
      if(!comp_by_coord(convex_hull_[farest1_start], convex_hull_[i])) {
	farest1_start = i;
      }
      if(comp_by_coord(convex_hull_[farest2_start], convex_hull_[i])) {
	farest2_start = i;
      }
    }
  }

  T ret2 = 0;
  {
    size_t farest1 = farest1_start;
    size_t farest2 = farest2_start;
    while(farest1 != farest2_start || farest2 != farest1_start) {
      ret2 = max(ret2, dist2(convex_hull_[farest1], convex_hull_[farest2]));
      Point2<T> diff = convex_hull_[(farest2+1)%m]-convex_hull_[farest2];
      if(convex_hull_[(farest1+1)%m].det(diff) < 0) {
	farest1 = (farest1+1) % m;
      }else {
	farest2 = (farest2+1) % m;
      }
    }
  }

  return sqrt(static_cast<double>(ret2));
}

template <typename T>
bool ConvexPolytope<T>::is_on_edges(const Point2<T>& p) {
  if(convex_hull_.empty()) {
    convex_hull();
  }
  size_t m = convex_hull_.size();
  for(size_t i = 0; i < m; ++i) {
    Point2<T>& q = convex_hull_[i];
    Point2<T>& r = convex_hull_[(i+1)%m];
    if(on_segment(Line<T>(q, r), p, true)) {
      return true;
    }
  }
  return false;
}

template <typename T>
bool ConvexPolytope<T>::is_interior(const Point2<T>& p) {
  if(convex_hull_.empty()) {
    convex_hull();
  }
  size_t m = convex_hull_.size();

  Point2<T>& q0 = convex_hull_[0];
  Point2<T>& r0 = convex_hull_[1];
  T det = (q0-p).det(r0-p);
  if(approx_zero(det)) {
    return false;
  }
  bool reference_dir = approx_negative(det);
  for(size_t i = 1; i < m; ++i) {
    Point2<T>& q = convex_hull_[i];
    Point2<T>& r = convex_hull_[(i+1)%m];
    T det = (q-p).det(r-p);
    if(approx_zero(det)) {
      return false;
    }
    bool dir = approx_negative(det);
    if(reference_dir != dir) {
      return false;
    }
  }
  return true;
}

#endif // CONVEX_POLYTOPE_IMPL_HPP__
