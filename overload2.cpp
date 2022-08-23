#include <array>
#include <cstdio>
#include <type_traits>

// expression template version of addition for DualNum uses the type
// DualNumSum to represent the unevaluated addition.

template <typename LHS, typename RHS>
class DualNumSum {
public:
  using value_type = typename LHS::value_type;

  DualNumSum(LHS const& lhs, RHS const& rhs) : lhs(lhs), rhs(rhs) {}

  // conversion of i'th element to the resulting sum of the i'th elements
  // of the represented expression.
  value_type
  operator()(std::size_t i) const
  {
    return lhs(i) + rhs(i);
  }

private:
  // We contain references to avoid copying. This is acceptable because the
  // lifetime of an expression object is always, by construction, long enough to
  // let it be evaluated.
  LHS const& lhs;
  RHS const& rhs;
};

// expression template version of multiplication for DualNum uses the type
// DualNumProduct to represent the unevaluated multiplication.

template <typename LHS, typename RHS>
class DualNumProduct {
public:
  using value_type = typename LHS::value_type;

  DualNumProduct(LHS const& lhs, RHS const& rhs) : lhs(lhs), rhs(rhs) {}

  // conversion of i'th element to the resulting sum of the i'th elements
  // of the represented expression.
  value_type
  operator()(std::size_t i) const
  {
    return i == 0 ? lhs(0) * rhs(0) : lhs(0) * rhs(1) + lhs(1) * rhs(0);
  }

private:
  // We contain references to avoid copying. This is acceptable because the
  // lifetime of an expression object is always, by construction, long enough to
  // let it be evaluated.
  LHS const& lhs;
  RHS const& rhs;
};

struct DualNum {
  // We need a nested type value_type, so that DualNum can be used
  // withh the DualNumSum template.
  using value_type = double;

  // We store our data in a fixed-size array so that we can access them
  // generically in the operators.
  std::array<value_type, 2> vals;

  // Serves as default constructor, as well as 1- and 2-arg constructors.
  DualNum() : vals{0.0, 0.0} {}
  DualNum(double real) : vals{real, 0.0} {}
  DualNum(double real, double dual) : vals{real, dual} {}

  // This constructor template is required to allow creating a DualNum from an
  // expression; operator= does not do this because it requires an
  // already-existing DualNum object.
  // This constructor is not explicit because we want to allow automatic
  // conversion from an expression into a DualNum.
  //
  // The type used as E must support operator()(std::size_t) const.
  // Both DualNumSum ad DualNum itself meet the requirement.
  template <typename E>
  DualNum(E const& expr) : vals{expr(0), expr(1)}
  {}

  // Note that DualNumSum has the same operator (only the const version).
  value_type
  operator()(std::size_t i) const
  {
    return vals[i];
  }

  value_type&
  operator()(std::size_t i)
  {
    return vals[i];
  }

  // This member template assignment operator evaluates an expression (such as
  // generated by DualNumSum) into the DualNum to which the assignment is made.
  // It merely evaluates each "slot" in the expression.
  template <typename E>
  DualNum&
  operator=(E const& expr)
  {
    vals[0] = expr(0);
    vals[1] = expr(1);
    return *this;
  }
};

// We support the suffix _dn on a floating-point literal, or an integer literal,
// to create a DualNum.
inline
DualNum operator "" _dn(long double x) {
  return DualNum(static_cast<double>(x));
}

inline
DualNum operator "" _dn(unsigned long long x) {
  return DualNum(static_cast<double>(x));
}

// Adding two expressions does not force evaluation of the expressions. This is
// the key element of the expression template abstraction.

template <typename LHS, typename RHS>
DualNumSum<LHS, RHS>
operator+(LHS const& lhs, RHS const& rhs)
{
  return DualNumSum<LHS, RHS>(lhs, rhs);
}

template <typename LHS, typename RHS>
DualNumProduct<LHS, RHS>
operator*(LHS const& lhs, RHS const& rhs)
{
  return DualNumProduct<LHS, RHS>(lhs, rhs);
}

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
