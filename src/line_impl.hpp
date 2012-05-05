#ifndef LINE_IMPL_HPP__
#define LINE_IMPL_HPP__

template <typename T>
Line<T>::Line(const Line<T>& p) : id_(p.id_), from_(p.from_), to_(p.to_){}

bool approx_zero(double d) {
  return abs(d) < eps;
}

bool approx_non_positive(double d) {
  return d < eps;
}

bool approx_negative(double d) {
  return d < -eps;
}

template <typename T>
bool on_segment(const Line<T> l,
		const Point2<T>& q,
		bool allow_ends = true) {
  if(allow_ends) {
    return approx_zero((l.from_-q).det(l.to_-q)) 
      && approx_non_positive((l.from_-q).dot(l.to_-q));
  }else {
    return approx_zero((l.from_-q).det(l.to_-q)) 
      && approx_negative((l.from_-q).dot(l.to_-q));
  }
}

// We assume l and m are not parallel
template <typename T>
Point2<T> intersection(const Line<T>& l,
		       const Line<T>& m) {
  const Point2<T>& p1 = l.from_;
  const Point2<T>& p2 = l.to_;
  const Point2<T>& q1 = m.from_;
  const Point2<T>& q2 = m.to_;
  return p1 + (p2-p1) * ( (q2-q1).det(q1-p1)/(q2-q1).det(p2-p1) );
}

template <typename T>
bool is_cross(const Line<T>& l,
	      const Line<T>& m,
	      bool allow_crossing_by_end = true) {
  if(approx_zero((l.from_-l.to_).det(m.from_-m.to_))) {
    return on_segment(l, m.from_, allow_crossing_by_end)
      || on_segment(l, m.to_, allow_crossing_by_end)
      || on_segment(m, l.from_, allow_crossing_by_end)
      || on_segment(m, l.to_, allow_crossing_by_end);
  }else {
    Point2<T> r = intersection(l, m);
    return on_segment(l, r, allow_crossing_by_end)
      && on_segment(m, r, allow_crossing_by_end);
  }
}

#endif // LINE_IMPL_HPP__
