#include "dual_num5.hh"
#include "multiply_3.hh"
#include "nanobench.h"


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