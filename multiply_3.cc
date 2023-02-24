#include "dual_num5.hh"
#include "multiply_3.hh"

#include <stdio.h>

void
print(DualNum5 const& x)
{
  printf("dual_num5 = ");
  for (int i = 0; i != 6; ++i) printf(" %f", x(i));
  printf("\n");
}

DualNum5
use_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  // return x * y * z;
  return use_mult_n(x, y, z);
}

DualNum5
fake_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
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
  return {a, b, c, d, e, f};
}
