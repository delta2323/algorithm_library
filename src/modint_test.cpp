#include <gtest/gtest.h>
#include "modint.hpp"

using namespace std;

TEST(modint, oridinal_usage1) {
  const int mod = 5;
  ModInt<mod> a(2);
  ASSERT_EQ(2, a.get());
  a += 4;
  ASSERT_EQ(1, a.get());  
  a -= 3;
  ASSERT_EQ(3, a.get());
  a *= 3;
  ASSERT_EQ(4, a.get());
  a /= 2;
  ASSERT_EQ(2, a.get());
  a /= 3;
  ASSERT_EQ(4, a.get());
}

TEST(modint, oridinal_usage2) {
  const int mod = 5;
  ModInt<mod> a(2);
  ModInt<mod> b(4);

  ASSERT_EQ(2, a.get());
  a += b;
  ASSERT_EQ(1, a.get());
  b = 3;
  a -= b;
  ASSERT_EQ(3, a.get());
  a *= b;
  ASSERT_EQ(4, a.get());
  b = 2;
  a /= b;
  ASSERT_EQ(2, a.get());
  b = 3;
  a /= b;
  ASSERT_EQ(4, a.get());
}

TEST(modint, oridinal_usage3) {
  const int mod = 5;
  ModInt<mod> a(2);
  ModInt<mod> b(4);
  ModInt<mod> c;

  c = a + b;
  ASSERT_EQ(1, c.get());

  c = a - b;
  ASSERT_EQ(3, c.get());

  c = a * b;
  ASSERT_EQ(3, c.get());

  c = a / b;
  ASSERT_EQ(3, c.get());
}

TEST(modint, print) {
  const int mod = 5;
  ModInt<mod> a(2);
  cout << a;
}

