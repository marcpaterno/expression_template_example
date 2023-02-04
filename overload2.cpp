#include "dual_num2.hpp"
#include <array>
#include <cstdio>
#include <type_traits>

int
main()
{
  DualNum x0(1.0, 0.5), x1(2.0, 1.5), x2(3.0, 2.5), x3(4.0, 3.5);
  DualNum y = x0 + x1 + x2 + x3 + DualNum(5.0);
  printf("outputs:  %f   %f\n", y(0), y(1));

  DualNum z;
  z = x0 * x1 * x2 * x3;
  printf("outputs:  %f   %f\n", z(0), z(1));

  DualNum z2;
  z2 = 1.0_dn + x0 * x1 * x2 * x3;
  printf("outputs:  %f   %f\n", z2(0), z2(1));

  DualNum z3;
  z3 = 1_dn + x0 * x1 * x2 * x3;
  printf("outputs:  %f   %f\n", z3(0), z3(1));
}
