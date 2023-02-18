#include "autodiff/forward/dual.hpp"
#include <tuple>

using autodiff::derivatives;
using autodiff::dual;
using autodiff::wrt;

inline dual
multiply_3(dual v, dual w, dual x, dual y, dual z)
{
  return v * w * x * y * z;
}

auto
func(dual v, dual w, dual x, dual y, dual z)
{
  dual const   f    = multiply_3(v, w, x, y, z);
  double const dfdv = derivative(multiply_3, wrt(v), at(v, w, x, y, z));
  double const dfdw = derivative(multiply_3, wrt(w), at(v, w, x, y, z));
  double const dfdx = derivative(multiply_3, wrt(x), at(v, w, x, y, z));
  double const dfdy = derivative(multiply_3, wrt(y), at(v, w, x, y, z));
  double const dfdz = derivative(multiply_3, wrt(z), at(v, w, x, y, z));
  return std::make_tuple(f, dfdv, dfdw, dfdx, dfdy, dfdz);
}
