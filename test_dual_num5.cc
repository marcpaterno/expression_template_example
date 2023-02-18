#include "catch2/catch_test_macros.hpp"

#include "dual_num5.hh"
#include <array>
#include <cstdio>
#include <type_traits>

DualNum5 w{-2.0, 7.0, 3.0, 4.0, 8.0, 11.0};
DualNum5 x{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
DualNum5 y{2.0, 3.5, 4.0, 5.0, 8.0, 9.0};

TEST_CASE("construct DualNum5s")
{
  DualNum5 x;
  CHECK(x(0) == 0.0);
  CHECK(x(1) == 0.0);
  CHECK(x(2) == 0.0);
  CHECK(x(3) == 0.0);
  CHECK(x(4) == 0.0);
  CHECK(x(5) == 0.0);

  DualNum5 y(1.0);
  CHECK(y(0) == 1.0);
  CHECK(y(1) == 0.0);
  CHECK(y(2) == 0.0);
  CHECK(y(3) == 0.0);
  CHECK(y(4) == 0.0);
  CHECK(y(5) == 0.0);

  DualNum5 z(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  CHECK(z(0) == 1.0);
  CHECK(z(1) == 2.0);
  CHECK(z(2) == 3.0);
  CHECK(z(3) == 4.0);
  CHECK(z(4) == 5.0);
  CHECK(z(5) == 6.0);
}

TEST_CASE("addition of DualNum5s")
{
  DualNum5 z = x + y;
  CHECK(z(0) == 3.0);
  CHECK(z(1) == 5.5);
  CHECK(z(2) == 7.0);
  CHECK(z(3) == 9.0);
  CHECK(z(4) == 13.0);
  CHECK(z(5) == 15.0);
}

TEST_CASE("subtraction of DualNum5s")
{
  DualNum5 w = x - y;
  CHECK(w(0) == -1.0);
  CHECK(w(1) == -1.5);
  CHECK(w(2) == -1.0);
  CHECK(w(3) == -1.0);
  CHECK(w(4) == -3.0);
  CHECK(w(5) == -3.0);
}

TEST_CASE("multiplication of DualNum5s")
{
  DualNum5 z = x * y;
  CHECK(z(0) == 2.0);
  CHECK(z(1) == 7.5);
  CHECK(z(2) == 10.0);
  CHECK(z(3) == 13.0);
  CHECK(z(4) == 18.0);
  CHECK(z(5) == 21.0);
}

TEST_CASE("literal DualNum5s")
{
  auto x = 1.0_dn;
  CHECK(x(0) == 1.0);
  CHECK(x(1) == 0.0);
  CHECK(x(2) == 0.0);
  CHECK(x(3) == 0.0);
  CHECK(x(4) == 0.0);

  auto y = 3_dn;
  CHECK(y(0) == 3.0);
}

TEST_CASE("add DualNum5 + double")
{
  DualNum5 z = x + 1.0;
  CHECK(z(0) == 2.0);
  CHECK(z(1) == 2.0);
  CHECK(z(2) == 3.0);
  CHECK(z(3) == 4.0);
  CHECK(z(4) == 5.0);
}

TEST_CASE("add double + DualNum5")
{
  DualNum5 z = 1.0 + x;
  CHECK(z(0) == 2.0);
  CHECK(z(1) == 2.0);
  CHECK(z(2) == 3.0);
  CHECK(z(3) == 4.0);
  CHECK(z(4) == 5.0);
}

TEST_CASE("multiply DualNum5 by double")
{
  DualNum5 z = x * 2.0;
  CHECK(z(0) == 2.0);
  CHECK(z(1) == 4.0);
  CHECK(z(2) == 6.0);
  CHECK(z(3) == 8.0);
  CHECK(z(4) == 10.0);
}

TEST_CASE("multiply double by DualNum5")
{
  DualNum5 z = 3.0 * x;
  CHECK(z(0) == 3.0);
  CHECK(z(1) == 6.0);
  CHECK(z(2) == 9.0);
  CHECK(z(3) == 12.0);
  CHECK(z(4) == 15.0);
  CHECK(z(5) == 18.0);
}

TEST_CASE("mixed expression with DualNum5s")
{
  SECTION("multiply then add")
  {
    // This is the value we want to check.
    DualNum5 z = w * x + y;

    // This is the expression evaluation broken down
    // into pieces.
    DualNum5 t1   = w * x;
    DualNum5 expr = t1 + y;
    CHECK(z == expr);
  }

  SECTION("add then multiply")
  {
    // This is the value we want to check.
    DualNum5 z = w + x * y;

    // This is the expression evaluation broken down
    // into pieces.
    DualNum5 t2   = x * y;
    DualNum5 expr = w + t2;
    CHECK(z == expr);
  }

  SECTION("respect these parentheses")
  {
    // This is the value we want to check.
    DualNum5 z = (w + x) * y;

    // This is the expression evaluation broken down into pieces.
    DualNum5 t1   = w + x;
    DualNum5 expr = t1 * y;
    CHECK(z == expr);
  }
}

TEST_CASE("addition expressions with bare doubles")
{
  DualNum5 tmp      = x + y;
  DualNum5 expected = tmp + 2.0;

  SECTION("double at end")
  {
    DualNum5 z = x + y + 2.0;
    CHECK(z == expected);
  }

  SECTION("double in middle")
  {
    DualNum5 z = x + 2.0 + y;
    CHECK(z == expected);
  }

  SECTION("double in the front")
  {
    DualNum5 z = 2.0 + x + y;
    CHECK(z == expected);
  }
}

TEST_CASE("multiplication expressions with bare doubles")
{
  SECTION("double at end")
  {
    DualNum5 z = x * y * 3.0;

    DualNum5 t1       = x * y;
    DualNum5 expected = t1 * DualNum5(3.0);
    CHECK(z == expected);
  }

  SECTION("double in the middle")
  {
    DualNum5 z = x * 3.0 * y;

    DualNum5 t1       = x * 3.0;
    DualNum5 expected = t1 * y;
    CHECK(z == expected);
  }

  SECTION("double in the front")
  {
    DualNum5 z = 3.0 * x * y;

    DualNum5 t1       = 3.0 * x;
    DualNum5 expected = t1 * y;
    CHECK(z == expected);
  }
}

TEST_CASE("subtraction expressions with bare doubles")
{
  SECTION("double at end")
  {
    DualNum5 z        = x - y - 2.0;
    DualNum5 tmp      = x - y;
    DualNum5 expected = tmp - 2.0;
    CHECK(z == expected);
  }

  SECTION("double in middle")
  {
    DualNum5 z        = x - 2.0 - y;
    DualNum5 tmp      = x - 2.0;
    DualNum5 expected = tmp - y;
    CHECK(z == expected);
  }

  SECTION("double in the front")
  {
    DualNum5 z        = 2.0 - x - y;
    DualNum5 tmp      = 2.0 - x;
    DualNum5 expected = tmp - y;
    CHECK(z == expected);
  }
}
