# Understanding Expression Template Efficiency

We are trying to understand how current compilers work with expression template code.
Expression templates are a C++ technique that uses class templates to represent unevaluated mathematical operations.
This allows the expressions to be evaluated only as needed, thus providing opportunities for an optimizing compiler to create efficient code.
In particular, we are trying to obtain a deep understanding of the relative performance of C-style mathematical code and expression template code for several different compilers.
We are doing this both by inspection of the assembly language produced by the compiler and by running micro-benchmarks to measure the performance.
Our initial work is being done with several versions of the GCC and Clang compilers generating code for CPUs.

We are eventually interested in making these observations for GPU-based code.
Once we have a sufficient understanding of how to analyze and benchmark the compiler output for the CPU, we will move to doing the same for the code generated for GPUs.

The code we are analyzing is under development at git@github.com:marcpaterno/expression_template_example.git.
We want to use this code to understand:
    1. The degree to which the compiler and optimizer is able to obtain optimal performance from each version of the code.
    2. The accuracy to which the benchmarking tools we have available are able to measure the performance.
    3. The style of the (C++) code that yields the best performance.

