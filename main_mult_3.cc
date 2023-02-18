// This program exercises the multiply_3 function using DualNum5.
#include "dual_num5.hh"
#include "multiply_3.hh"

template <typename T>
void whatis(T&&);

int
main()
{
  DualNum5 a{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  DualNum5 b{2.0, 3.0, 4.0, 5.0, 6.0, 1.0};
  DualNum5 c{3.0, 4.5, 5.0, 6.0, 1.0, 2.0};
  // DualNum5 d {4.0, 5.0, 6.0, 1.0, 2.0, 3.0};
  // DualNum5 e {5.0, 6.0, 1.0, 2.0, 3.0, 4.0};
  DualNum5 z = mult_3(a, b, c);
  // whatis(mult_3(a,b,c));

  print(z);
}
