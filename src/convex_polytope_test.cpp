#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

#include "convex_polytope.hpp"

using namespace std;

class TriangleTest : public ::testing::Test {
public:
protected:
  virtual void SetUp() {
    n = 3;
    ps.clear();
    ps.push_back(Point2<int>(200, 0, 0));
    ps.push_back(Point2<int>(100, 1, 0));
    ps.push_back(Point2<int>(0  , 0, 1));
    cp = new ConvexPolytope<int>(ps);
  }
  virtual void TearDown() {}

protected:
  int n;
  ConvexPolytope<int>* cp;
private:
  vector<Point2<int> > ps;
};

TEST_F(TriangleTest, convex_hull) {
  vector<Point2<int> > outer;
  cp->get_convex_hull(outer);
  sort(outer.begin(), outer.end(), comp_by_id<int>);
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

class SquareTest : public ::testing::Test {
public:
protected:
  virtual void SetUp() {
    n = 5;
    ps.clear();
    ps.push_back(Point2<int>(40,  0,  0));
    ps.push_back(Point2<int>( 0,  1,  0));
    ps.push_back(Point2<int>(10,  0,  1));
    ps.push_back(Point2<int>(20, -1,  0));
    ps.push_back(Point2<int>(30,  0, -1));

    cp = new ConvexPolytope<int>(ps);
  }
  virtual void TearDown() {}

protected:
  int n;
  ConvexPolytope<int>* cp;
private:
  vector<Point2<int> > ps;
};

TEST_F(SquareTest, convex_hull) {
  vector<Point2<int> > actual;
  cp->get_convex_hull(actual);
  sort(actual.begin(), actual.end(), comp_by_id<int>);

  int m = 4;
  ASSERT_EQ(m, actual.size());
  for(int i = 0; i < m; ++i) {
    ASSERT_EQ(i*10, actual[i].id_);
  }
}

TEST_F(SquareTest, diameter) {
  ASSERT_DOUBLE_EQ(2, cp->diameter());
}



