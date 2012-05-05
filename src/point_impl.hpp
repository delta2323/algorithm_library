#ifndef POINT_IMPL_HPP__
#define POINT_IMPL_HPP__

template <typename T>
Point2<T>::Point2(const Point2<T>& p) : id_(p.id_), x_(p.x_), y_(p.y_){}

template <typename T>
Point2<T> Point2<T>::operator+=(const Point2<T>& p) {
  {
    Point2<T> tmp(id_, x_+p.x_, y_+p.y_);
    swap(tmp, *this);
  }
  return *this;
}

template <typename T>
Point2<T> Point2<T>::operator+(const Point2<T>& p) const {
  Point2<T> tmp(*this);
  tmp += p;
  return tmp;
}

template <typename T>
Point2<T> Point2<T>::operator-=(const Point2<T>& p) {
  {
    Point2<T> tmp(id_, x_-p.x_, y_-p.y_);
    swap(tmp, *this);
  }
  return *this;
}

template <typename T>
Point2<T> Point2<T>::operator-(const Point2<T>& p) const {
  Point2<T> tmp(*this);
  tmp -= p;
  return tmp;
}

template <typename T>
Point2<T> Point2<T>::operator*=(T k) {
  {
    Point2<T> tmp(id_, k*x_, k*y_);
    swap(tmp, *this);
  }
  return *this;
}

template <typename T>
Point2<T> Point2<T>::operator*(T k) const {
  Point2<T> tmp(*this);
  tmp *= k;
  return tmp;
}

template <typename T>
T Point2<T>::dot(const Point2<T>& p) const {
  return x_*p.x_+y_*p.y_;
}

template <typename T>
T Point2<T>::det(const Point2<T>& p) const {
  return x_*p.y_-y_*p.x_;
}

template <typename T>
T Point2<T>::dist2() const {
  return x_*x_+y_*y_;
}

template <typename T>
bool comp_by_id(const Point2<T>& p, const Point2<T>& q) {
  return p.id_ < q.id_;
}

template <typename T>
bool comp_by_coord(const Point2<T>& p, const Point2<T>& q) {
  if(p.x_ != q.x_) {
    return p.x_ < q.x_;
  }else {
    return p.y_ < q.y_;
  }
}

template <typename T>
T dist2(const Point2<T>& p, const Point2<T>& q) {
  return (p-q).dist2();
}


#endif // POINT_IMPL_HPP__
