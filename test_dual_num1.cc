#include "catch.hpp"
#include "dual_num1.hh"
#include <array>
#include <cstdio>
#include <type_traits>

inline int
printf(DualNum x)
{
  return printf("output: %f  %f\n", x(0), x(1));
}

TEST_CASE("construct DualNums")
{
  DualNum x;
  CHECK(x(0) == 0.0);
  CHECK(x(1) == 0.0);

  DualNum y(1.0);
  CHECK(y(0) == 1.0);
  CHECK(y(1) == 0.0);

  DualNum z(1.0, 2.5);
  CHECK(z(0) == 1.0);
  CHECK(z(1) == 2.5);
}

TEST_CASE("addition of DualNums")
{
  DualNum x(1.0, 2.0);
  DualNum y(3.0, 4.0);
  DualNum z = x + y;
  CHECK(z(0) == 4.0);
  CHECK(z(1) == 6.0);
}

TEST_CASE("subtraction of DualNums")
{
  DualNum x(1.0, 2.0);
  DualNum y(3.0, 4.0);
  DualNum w = x - y;
  CHECK(w(0) == -2.0);
  CHECK(w(1) == -2.0);
}

TEST_CASE("multiplication of DualNums")
{
  DualNum x(1.0, 2.0);
  DualNum y(3.0, 4.0);
  DualNum z = x * y;
  CHECK(z(0) == 3.0);
  CHECK(z(1) == 10.0);
}

TEST_CASE("literal DualNums")
{
  auto x = 1.0_dn;
  CHECK(x(0) == 1.0);
  CHECK(x(1) == 0.0);

  auto y = 3_dn;
  CHECK(y(0) == 3.0);
  CHECK(y(1) == 0.0);
}

TEST_CASE("add DualNum + double")
{
  DualNum x(1.0, -1.0);
  DualNum z = x + 1.0;
  CHECK(z(0) == 2.0);
  CHECK(z(1) == -1.0);
}

TEST_CASE("add double + DualNum")
{
  DualNum x(1.0, -1.0);
  DualNum z = 1.0 + x;
  CHECK(z(0) == 2.0);
  CHECK(z(1) == -1.0);
}

TEST_CASE("multiply DualNum by double")
{
  DualNum x(2.0, 3.0);
  DualNum z = x * 2.0;
  CHECK(z(0) == 4.0);
  CHECK(z(1) == 6.0);
}

TEST_CASE("multiply double by DualNum")
{
  DualNum x(2.0, 3.0);
  DualNum z = 3.0 * x;
  CHECK(z(0) == 6.0);
  CHECK(z(1) == 9.0);
}

TEST_CASE("mixed expression with DualNums")
{
  DualNum w(-1.0, -3.0);
  DualNum x(1.0, 2.0);
  DualNum y(3.0, 4.0);

  SECTION("multiply then add")
  {
    // This is the value we want to check.
    DualNum z = w * x + y;

    // This is the expression evaluation broken down
    // into pieces.
    DualNum t1 = w * x;
    DualNum expr = t1 + y;
    CHECK(z == expr);
  }

  SECTION("add then multiply")
  {
    // This is the value we want to check.
    DualNum z = w + x * y;

    // This is the expression evaluation broken down
    // into pieces.
    DualNum t2 = x * y;
    DualNum expr = w + t2;
    CHECK(z == expr);
  }

  SECTION("respect these parentheses")
  {
    // This is the value we want to check.
    DualNum z = (w + x) * y;

    // This is the expression evaluation broken down into pieces.
    DualNum t1 = w + x;
    DualNum expr = t1 * y;
    CHECK(z == expr);
  }
}

TEST_CASE("addition expressions with bare doubles")
{
  DualNum x(-1.0, 1.0);
  DualNum y(2.0, 3.0);

  SECTION("double at end")
  {
    DualNum z = x + y + 2.0;
    CHECK(z(0) == 3.0);
    CHECK(z(1) == 4.0);
  }

  SECTION("double in middle")
  {
    DualNum z = x + 2.0 + y;
    CHECK(z(0) == 3.0);
    CHECK(z(1) == 4.0);
  }

  SECTION("double in the front")
  {
    DualNum z = 2.0 + x + y;
    CHECK(z(0) == 3.0);
    CHECK(z(1) == 4.0);
  }
}

TEST_CASE("multiplication expressions with bare doubles")
{
  DualNum x(1.0, 2.0);
  DualNum y(3.0, -1.0);

  SECTION("double at end")
  {
    DualNum z = x * y * 3.0;

    DualNum t1 = x * y;
    DualNum expected = t1 * DualNum(3.0);
    CHECK(z == expected);
  }

  SECTION("double in the middle")
  {
    DualNum z = x * 3.0 * y;

    DualNum t1 = x * 3.0;
    DualNum expected = t1 * y;
    CHECK(z == expected);
  }

  SECTION("double in the front")
  {
    DualNum z = 3.0 * x * y;

    DualNum t1 = 3.0 * x;
    DualNum expected = t1 * y;
    CHECK(z == expected);
  }
}

TEST_CASE("subtraction expressions with bare doubles")
{
  DualNum x(-1.0, 1.0);
  DualNum y(2.0, 3.0);

  SECTION("double at end")
  {
    DualNum z = x - y - 2.0;
    CHECK(z(0) == -5.0);
    CHECK(z(1) == -2.0);
  }

  SECTION("double in middle")
  {
    DualNum z = x - 2.0 - y;
    CHECK(z(0) == -5.0);
    CHECK(z(1) == -2.0);
  }

  SECTION("double in the front")
  {
    DualNum z = 2.0 - x - y;
    CHECK(z(0) == 1.0);
    CHECK(z(1) == -4.0);
  }
}