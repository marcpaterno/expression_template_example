#include "dual_num5.hh"
#include "multiply_3.hh"

DualNum5
use_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  // Return relies on automatic conversion from expression to DualNum5
  return x * y * z;
}
