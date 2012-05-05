#ifndef LINE_HPP__
#define LINE_HPP__

#include "point.hpp"

// 2012/05/05 Kenta OONO
// This module works only when T = double

template <typename T>
struct Line {
  const static int kINVALID = -1;
  int id_;
  Point2<T> from_;
  Point2<T> to_;
  Line(){}
  Line(const Line& p);
  Line(int id, Point2<T> from, Point2<T> to) : id_(id), from_(from), to_(to) {}
  Line(Point2<T> from, Point2<T> to) : id_(kINVALID), from_(from), to_(to) {}
};

template <typename T>
bool on_segment(const Line<T> l,
		const Point2<T>& p,
		bool allow_ends = true);
template <typename T>
Point2<T> intersection(const Line<T>& l,
			    const Line<T>& m);
template <typename T>
bool is_cross(const Line<T>& l,
	      const Line<T>& m,
	      bool allow_crossing_by_end = true);

#include "line_impl.hpp"

#endif // LINE_HPP_
