#include "dual_num5.hh"
#include "multiply_3.hh"
#include "nanobench.h"

template <typename F>
void run_bench(F func, ankerl::nanobench::Bench* bench, char const* name) {
  DualNum5 w{-2.0, 7.0, 3.0, 4.0, 8.0, 11.0};
  DualNum5 x{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  DualNum5 y{2.0, 3.5, 4.0, 5.0, 8.0, 9.0};
  bench->run(name, [&]() {
    DualNum5 z = func(w, x, y);
    ankerl::nanobench::doNotOptimizeAway(z);
  });
}
int
main()
{
  ankerl::nanobench::Bench b;
   b.title("dual num tests");
   b.warmup(10);
   b.performanceCounters(true);
   b.epochs(10000);
  run_bench(&use_mult_3, &b, "expression template use");
  run_bench(&fake_mult_3, &b, "by-hand expansion");
}

