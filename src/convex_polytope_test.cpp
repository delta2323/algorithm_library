#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

#include "convex_polytope.hpp"

using namespace std;

const static Point2<double> v[6] = { Point2<double>(200, 0, 0),
				     Point2<double>(100, 1, 0),
				     Point2<double>(0  , 0, 1), // vertices
				     Point2<double>(500, 0, 0.5),
				     Point2<double>(400, 0.5, 0),
				     Point2<double>(300, 0.5, 0.5) }; // midpoints
class TriangleTest : public ::testing::TestWithParam<Point2<double> > {
public:
protected:
  TriangleTest() :n(3) {}
  virtual void SetUp() {
    ps.clear(); ps.assign(v, v+n);
    cp = new ConvexPolytope<double>(ps);
  }
  virtual void TearDown() {}
protected:
  int n;
  ConvexPolytope<double>* cp;
private:
  vector<Point2<double> > ps;
};

TEST_F(TriangleTest, convex_hull) {
  vector<Point2<double> > outer;
  cp->get_convex_hull(outer);
  sort(outer.begin(), outer.end(), comp_by_id<double>);
  ASSERT_EQ(n, outer.size());
  for(int i = 0; i < n; ++i) {
    ASSERT_EQ(i*100, outer[i].id_);
  }
}

TEST_F(TriangleTest, diameter) {
  ASSERT_DOUBLE_EQ(sqrt(2), cp->diameter());
}

// 2012/04/30 Kenta OONO <oono@preferred.jp>
// In CovexPolyTope<T>::convex_hull, ConvexPolyTope<T>::ps_ is sorted
// and could be different order from when it was given to ConvexPolyTope<T>.
// So, if we want to access to points,  we must remember them.
// Alternative choice is to search by Point2<T>::id_.
/*
TEST_F(TriangleTest, get_point) {
  for(int i = 0; i < 3; ++i) {
    ASSERT_EQ(200-i*100, (*cp)[i].id_);
  }
}
*/

TEST_F(TriangleTest, is_interior_ordinal) {
  Point2<double> o(300, 0.2, 0.2);
  ASSERT_TRUE(cp->is_interior(o));
}
TEST_F(TriangleTest, is_on_edges_ordinal) {
  Point2<double> o(300, 0.2, 0.2);
  ASSERT_FALSE(cp->is_on_edges(o));
}

INSTANTIATE_TEST_CASE_P(TriangleTestInstance,
                        TriangleTest,
                        testing::ValuesIn(v));
TEST_P(TriangleTest, is_interior_circumstances) {
  ASSERT_FALSE(cp->is_interior(GetParam()));
}
TEST_P(TriangleTest, is_on_edges_circumstances) {
  ASSERT_TRUE(cp->is_on_edges(GetParam()));
}

class SquareTest : public ::testing::Test {
public:
protected:
  virtual void SetUp() {
    n = 5;
    ps.clear();
    ps.push_back(Point2<double>(40,  0,  0));
    ps.push_back(Point2<double>( 0,  1,  0));
    ps.push_back(Point2<double>(10,  0,  1));
    ps.push_back(Point2<double>(20, -1,  0));
    ps.push_back(Point2<double>(30,  0, -1));

    cp = new ConvexPolytope<double>(ps);
  }
  virtual void TearDown() {}

protected:
  int n;
  ConvexPolytope<double>* cp;
private:
  vector<Point2<double> > ps;
};

TEST_F(SquareTest, convex_hull) {
  vector<Point2<double> > actual;
  cp->get_convex_hull(actual);
  sort(actual.begin(), actual.end(), comp_by_id<double>);

  int m = 4;
  ASSERT_EQ(m, actual.size());
  for(int i = 0; i < m; ++i) {
    ASSERT_EQ(i*10, actual[i].id_);
  }
}

TEST_F(SquareTest, diameter) {
  ASSERT_DOUBLE_EQ(2, cp->diameter());
}



