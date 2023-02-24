#include "catch2/catch_test_macros.hpp"

#include "dual_num5.hh"
#include "multiply_3.hh"

DualNum5 w{-2.0, 7.0, 3.0, 4.0, 8.0, 11.0};
DualNum5 x{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
DualNum5 y{2.0, 3.5, 4.0, 5.0, 8.0, 9.0};

TEST_CASE("use_mult_3 and fake_mult_3 do the same thing")
{
  auto a = use_mult_3(w, x, y);
  auto b = fake_mult_3(w, x, y);
  CHECK(a == b);
  // auto c = left_fold_mult_3(w, x, y);
  // CHECK(a == c);
  auto d = right_fold_mult_3(w, x, y);
  CHECK(a == d);
}