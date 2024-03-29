#ifndef MULTIPLY_3_HH
#define MULTIPLY_3_HH

#include "dual_num5.hh"

// This is an inline implementation of the multiplication of 3 DualNum5 objects.
// It is inline for two reasons:
//   1. This allows us to declare the return type with auto, rather than
//   spelling out the complicated expression template type.
//   2. This allows the compiler to see the whole expression at the site of use,
//   thus providing the best opportunities for optimization.
inline
auto
mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z)
{
  return x * y * z;
}

// This is a non-inline function that uses mult_3 internally. It exists so that
// we can see how well the compiler is optimizing the expression template use.
DualNum5 use_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z);
DualNum5 handopt(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z);
DualNum5 long_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z);
DualNum5 left_fold_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z);
DualNum5 right_fold_mult_3(DualNum5 const& x, DualNum5 const& y, DualNum5 const& z);

DualNum5 only_construct(double a, double b, double c, double d, double e, double f);
  
template <typename... Args>
DualNum5
left_fold_mult_n(Args&&... args)
{
  return (... * args);
}

template <typename... Args>
DualNum5
right_fold_mult_n(Args&& ... args)
{
  return (args * ...);
}

#endif
