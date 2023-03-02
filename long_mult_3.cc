#include "dual_num5.hh"
#include "multiply_3.hh"

DualNum5
long_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  double a = x(0) * y(0) * z(0);
  double b = x(0) * y(0) * z(1) + x(0) * z(0) * y(1) + y(0) * z(0) * x(1);
  double c = x(0) * y(0) * z(2) + x(0) * z(0) * y(2) + y(0) * z(0) * x(2);
  double d = x(0) * y(0) * z(3) + x(0) * z(0) * y(3) + y(0) * z(0) * x(3);
  double e = x(0) * y(0) * z(4) + x(0) * z(0) * y(4) + y(0) * z(0) * x(4);
  double f = x(0) * y(0) * z(5) + x(0) * z(0) * y(5) + y(0) * z(0) * x(5);
  // Return uses DualNum5 constructor using 6 doubles
  return {a, b, c, d, e, f};
}
