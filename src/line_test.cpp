#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <utility>

#include "line.hpp"
#include "point.hpp"

using namespace std;

class SegmentTest : public ::testing::Test {
public:
  static const Line<double> l;
  static const Line<double> m;
  static const Point2<double> p;
  static const Point2<double> q;
  static const Point2<double> r;
  static const Line<double> a;
  static const Line<double> b;
  static const Line<double> c;
protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

const Line<double> SegmentTest::l(Line<double>(Point2<double>(-1, 0), Point2<double>(1, 0)));
const Line<double> SegmentTest::m(Line<double>(Point2<double>(-1, 1), Point2<double>(1, 1)));
const Point2<double> SegmentTest::p(Point2<double>(-1, 0));
const Point2<double> SegmentTest::q(Point2<double>(0, 0));
const Point2<double> SegmentTest::r(Point2<double>(1, 0));
const Line<double> SegmentTest::a(Line<double>(Point2<double>(-1, -1), Point2<double>(-1, 1)));
const Line<double> SegmentTest::b(Line<double>(Point2<double>(0, -1), Point2<double>(0, 1)));
const Line<double> SegmentTest::c(Line<double>(Point2<double>(1, -1), Point2<double>(1, 1)));

TEST_F(SegmentTest, on_segment_include_ends1) {
  ASSERT_TRUE(on_segment(l, p, true));
}
TEST_F(SegmentTest, on_segment_include_ends2) {
  ASSERT_TRUE(on_segment(l, q, true));
}
TEST_F(SegmentTest, on_segment_include_ends3) {
  ASSERT_TRUE(on_segment(l, r, true));
}

TEST_F(SegmentTest, on_segment_exclude_ends1) {
  ASSERT_FALSE(on_segment(l, p, false));
}
TEST_F(SegmentTest, on_segment_exclude_ends2) {
  ASSERT_TRUE(on_segment(l, q, false));
}
TEST_F(SegmentTest, on_segment_exclude_ends3) {
  ASSERT_FALSE(on_segment(l, r, false));
}

TEST_F(SegmentTest, is_cross_include_ends1) {
  ASSERT_TRUE(is_cross(l, a, true));
}
TEST_F(SegmentTest, is_cross_include_ends2) {
  ASSERT_TRUE(is_cross(l, b, true));
}
TEST_F(SegmentTest, is_cross_include_ends3) {
  ASSERT_TRUE(is_cross(l, c, true));
}

TEST_F(SegmentTest, is_cross_exclude_ends1) {
  ASSERT_FALSE(is_cross(l, a, false));
}
TEST_F(SegmentTest, is_cross_exclude_ends2) {
  ASSERT_TRUE(is_cross(l, b, false));
}
TEST_F(SegmentTest, is_cross_exclude_ends3) {
  ASSERT_FALSE(is_cross(l, c, false));
}

TEST_F(SegmentTest, is_cross_include_ends4) {
  ASSERT_TRUE(is_cross(m, a, true));
}
TEST_F(SegmentTest, is_cross_include_ends5) {
  ASSERT_TRUE(is_cross(m, b, true));
}
TEST_F(SegmentTest, is_cross_include_ends6) {
  ASSERT_TRUE(is_cross(m, c, true));
}

TEST_F(SegmentTest, is_cross_exclude_ends4) {
  ASSERT_FALSE(is_cross(m, a, false));
}
TEST_F(SegmentTest, is_cross_exclude_ends5) {
  ASSERT_FALSE(is_cross(m, b, false));
}
TEST_F(SegmentTest, is_cross_exclude_ends6) {
  ASSERT_FALSE(is_cross(m, c, false));
}



