#include "dual_num5.hh"
#include "multiply_3.hh"
#include "nanobench.h"

#include <iostream>

#include <chrono>
#include <thread>

DualNum5
only_construct(DualNum5 const&, DualNum5 const&, DualNum5 const&)
{
  return {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
}

template <typename F>
void
run_bench(F func, ankerl::nanobench::Bench* bench, char const* name)
{
  ankerl::nanobench::Rng rng(137);
  auto                   gen = [&]() { return rng.uniform01(); };
  DualNum5 w{gen(), gen(), gen(), gen(), gen(), gen()};
  DualNum5 x{gen(), gen(), gen(), gen(), gen(), gen()};
  DualNum5 y{gen(), gen(), gen(), gen(), gen(), gen()};
  DualNum5 z;
  bench->run(name, [&]() {
    z = func(w, x, y);
  });
  ankerl::nanobench::doNotOptimizeAway(z);
}

int
main()
{
  ankerl::nanobench::Bench b;
  b.title("dual num tests")
    .performanceCounters(true)
    .minEpochIterations(55*1000*1000);
  run_bench(&use_mult_3, &b, "expression template use");
  run_bench(&fake_mult_3, &b, "by-hand expansion");
  run_bench(&only_construct, &b, "only construct");
}
