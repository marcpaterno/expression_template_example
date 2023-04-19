#include "catch2/catch_test_macros.hpp"

#include <ostream>

#include "dual_num5.hh"
#include "multiply_3.hh"

std::ostream&
operator<<(std::ostream& os, DualNum5 const& x)
{
  os << "DualNum5: " << x(0);
  for (int i = 1; i < 6; ++i) os << ", " << x(i);
  return os;
}

DualNum5 w{-2.0, 7.0, 3.0, 4.0, 8.0, 11.0};
DualNum5 x{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
DualNum5 y{2.0, 3.5, 4.0, 5.0, 8.0, 9.0};

DualNum5 expected = handopt(w, x, y);

TEST_CASE("expression")
{
  DualNum5 z = use_mult_3(w, x, y);
  CHECK(z == expected);
}

TEST_CASE("fold")
{
  DualNum5 z = right_fold_mult_3(w, x, y);
  CHECK(z == expected);
}

TEST_CASE("long")
{
  DualNum5 z = long_mult_3(w, x, y);
  CHECK(z == expected);
}
