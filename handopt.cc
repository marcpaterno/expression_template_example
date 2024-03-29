#include "dual_num5.hh"
#include "multiply_3.hh"

DualNum5
handopt(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  double t1 = x(0) * y(0);
  double t2 = x(0) * z(0);
  double t3 = y(0) * z(0);

  double a = t1 * z(0);
  double b = t1 * z(1) + t2 * y(1) + t3 * x(1);
  double c = t1 * z(2) + t2 * y(2) + t3 * x(2);
  double d = t1 * z(3) + t2 * y(3) + t3 * x(3);
  double e = t1 * z(4) + t2 * y(4) + t3 * x(4);
  double f = t1 * z(5) + t2 * y(5) + t3 * x(5);
  // Return uses DualNum5 constructor using 6 doubles
  return {a, b, c, d, e, f};
}
