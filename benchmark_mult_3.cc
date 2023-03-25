#include "dual_num5.hh"
#include "multiply_3.hh"
#include "nanobench.h"

#include <iostream>

#include <chrono>
#include <thread>

template <typename F>
void
run_bench(F func, ankerl::nanobench::Bench* bench, char const* name)
{
  ankerl::nanobench::Rng rng(137);
  auto                   gen = [&]() { return rng.uniform01(); };
  DualNum5               w{gen(), gen(), gen(), gen(), gen(), gen()};
  DualNum5               x{gen(), gen(), gen(), gen(), gen(), gen()};
  DualNum5               y{gen(), gen(), gen(), gen(), gen(), gen()};
  bench->run(name, [&]() {
    DualNum5 z = func(w, x, y);
    ankerl::nanobench::doNotOptimizeAway(z);
  });
}

void
run_bench_constructor(ankerl::nanobench::Bench* bench, char const* name)
{
  ankerl::nanobench::Rng rng(137);
  auto                   gen = [&]() { return rng.uniform01(); };
  double args[6]  __attribute__((aligned(16))) = {gen(), gen(), gen(), gen(), gen(), gen()};
  bench->run(name, [&]() {
    DualNum5 z = only_construct(args[0], args[1], args[2], args[3],  args[4], args[5]);
    ankerl::nanobench::doNotOptimizeAway(z);
  });
}

int
main()
{
  ankerl::nanobench::Bench b;
  b.title("dual num tests")
    .performanceCounters(true)
    .minEpochIterations(55 * 1000 * 1000);
  run_bench(&right_fold_mult_3, &b, "right fold");
  run_bench(&use_mult_3, &b, "expression template use");
  run_bench(&fake_mult_3, &b, "by-hand expansion");
  run_bench(&long_mult_3, &b, "compiler expansion");
  // run_bench(&left_fold_mult_3, &b, "left fold");
  run_bench_constructor(&b, "only construct");
}
