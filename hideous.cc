#include "dual_num5.hh"

DualNum5
hideous(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  DualNum5 result = x * y * z;
  return result;
}