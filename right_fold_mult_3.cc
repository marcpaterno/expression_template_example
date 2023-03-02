#include "dual_num5.hh"
#include "multiply_3.hh"

// DualNum5
// left_fold_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
// {
//   return left_fold_mult_n(x, y, z);
// }

DualNum5
right_fold_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  // Return relies on automatic conversion from expression to DualNum5
  return right_fold_mult_n(x, y, z);
}
