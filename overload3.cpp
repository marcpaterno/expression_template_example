#include "dual_num3.hpp"

#include <cstdio>

int
main()
{
  duals::DualNum a;
  printf("default constructed: %f  %f\n", real(a), dual(a));

  duals::DualNum b(1.0, 0.5);
  printf("value constructed:   %f  %f\n", real(b), dual(b));

  duals::DualNum c(2.0);
  printf("value constructed:   %f  %f\n", real(c), dual(c));

  duals::DualNum s = b + c;
  printf("sum:                 %f  %f\n", real(s), dual(s));


  // DualNum x0(1.0, 0.5), x1(2.0, 1.5), x2(3.0, 2.5), x3(4.0, 3.5);
  // DualNum y = x0 + x1 + x2 + x3 + 5.0;
  // printf("outputs:  %f   %f\n", y.real(), y.dual());

  // DualNum z;
  // z = x0 * x1 * x2 * x3;
  // printf("outputs:  %f   %f\n", z.real(), z.dual());
}
