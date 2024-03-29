cmake_minimum_required(VERSION 3.20.0)
project(dual_num VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_compile_options(-Wall -Wextra -Wpedantic -Ofast -march=native -mfma -funsafe-math-optimizations -ffinite-math-only -fno-signed-zeros -funroll-loops -fverbose-asm -mprefer-vector-width=128 -momit-leaf-frame-pointer)

if($CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-mpreferred-stack-boundary=4 -malign-data=cacheline)
endif()

Include(FetchContent)

# We use catch2 (version 3) for testing.
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

# We use nanobench for simple benchmarking
FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.1.0
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

add_library(dual_num5_stuff OBJECT handopt.cc long_mult_3.cc only_construct.cc right_fold_mult_3.cc use_mult_3.cc run_bench_constructor.cc)
target_link_libraries(dual_num5_stuff PRIVATE nanobench)

add_executable(test_dual_num5 test_dual_num5.cc)
target_link_libraries(test_dual_num5 PRIVATE Catch2::Catch2WithMain)
add_test(test_dual_num5 test_dual_num5)

add_executable(test_mult_3 test_mult_3.cc)
target_link_libraries(test_mult_3 PRIVATE Catch2::Catch2WithMain dual_num5_stuff)
add_test(test_mult_3 test_mult_3)

add_executable(benchmark_mult_3 benchmark_mult_3.cc)
target_link_libraries(benchmark_mult_3 PRIVATE dual_num5_stuff nanobench)
