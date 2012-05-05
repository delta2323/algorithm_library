#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <utility>

#include "point.hpp"

using namespace std;

class SquareTest : public ::testing::Test {
public:
  static const Point2<double> p;
  static const Point2<double> q;
  static const Point2<double> r;
  static const Point2<double> s;
protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

const Point2<double> SquareTest::p(Point2<double>( 0, 0, 0));
const Point2<double> SquareTest::q(Point2<double>(10, 1, 0));
const Point2<double> SquareTest::r(Point2<double>(20, 1, 1));
const Point2<double> SquareTest::s(Point2<double>(30, 0, 1));

TEST_F(SquareTest, dot_orthogonal) {
  ASSERT_EQ(0, q.dot(s));
}
TEST_F(SquareTest, det_orthogonal) {
  ASSERT_EQ(1, q.det(s));
}

TEST_F(SquareTest, dot_diag_and_side) {
  ASSERT_EQ(1, q.dot(r));
}
TEST_F(SquareTest, det_diag_and_side) {
  ASSERT_DOUBLE_EQ(1, q.dot(r));
}

TEST_F(SquareTest, dot_opposite_diection_sides) {
  ASSERT_EQ(-1, (s-r).dot(q));
}
TEST_F(SquareTest, det_opposite_diection_sides) {
  ASSERT_EQ(0, (s-r).det(q));
}

