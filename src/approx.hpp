#ifndef APPROX_HPP__
#define APPROX_HPP__

#include <iostream>

const static double eps = 1e-10;

double abs_f(double d) {
  return d > 0 ? d : -d;
}

bool approx_zero(double d) {
  return abs_f(d) < eps;
}

bool approx_non_positive(double d) {
  return d < eps;
}

bool approx_negative(double d) {
  return d < -eps;
}

#endif // APPROX_HPP__
