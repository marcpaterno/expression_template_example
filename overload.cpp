#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct DualNum {
  double v_real, v_dual;

  explicit DualNum(double real = 0.0, double dual = 0.0)
    : v_real(real), v_dual(dual)
  {}
};

// simple add, mult support only

DualNum
operator+(const DualNum& op1, const DualNum& op2)
{
  DualNum tvar;
  tvar.v_real = op1.v_real + op2.v_real;
  tvar.v_dual = op1.v_dual + op2.v_dual;
  return tvar;
}

DualNum
operator*(const DualNum& op1, const DualNum& op2)
{
  DualNum tvar;
  tvar.v_real = op1.v_real * op2.v_real;
  tvar.v_dual = op1.v_real * op2.v_dual + op1.v_dual * op2.v_real;
  return tvar;
}

int
main()
{
  DualNum x0(1.0, 0.5), x1(2.0, 1.5), x2(3.0, 2.5), x3(4.0, 3.5);
  DualNum y = x0 + x1 + x2 + x3;
  printf("outputs:  %f   %f\n", y.v_real, y.v_dual);

  y = x0 * x1 * x2 * x3;
  printf("outputs:  %f   %f\n", y.v_real, y.v_dual);
}
