#ifndef CONVEX_POLYTOPE_HPP__
#define CONVEX_POLYTOPE_HPP__

#include <iostream>
#include <vector>
#include <cmath>

#include "point.hpp"

// Calculation of convex_hull (using Graham Scan) and
// diameter (using rotating caliper method) of given set of points.
// Original implementation is from "Programming Contest Challenge Book (2nd ed.)"  pp234-236

template <typename T>
class ConvexPolytope {
public:
  ConvexPolytope(const std::vector<Point2<T> >& ps);
  void get_convex_hull(std::vector<Point2<T> >& ret);
  double diameter();
  bool is_inside(const Point2<T>& p) const; // not implemeted yet.
private:
  const static double kINVALID = -1.f;
  void convex_hull();
  bool is_already_calc_diameter() const;
  double calc_diameter() const;
  std::vector<Point2<T> > ps_;
  std::vector<Point2<T> > convex_hull_;
  double diameter_;
};

#include "convex_polytope_impl.hpp"

#endif // CONVEX_POLYTOPE_HPP__
