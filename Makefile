CXX=g++-12
CLANG_DUMP_FLAGS=-Xclang -ast-print -fsyntax-only
CXXFLAGS=-Ofast -std=c++17 -Wall -Wextra -mfma -march=native # -fsanitize=address

.PHONY: test

all:  test_dual_num1 test_dual_num5 multiply_3.s multiply_3_autodiff.s main_mult_3

clean:
	rm -f overload test_dual_num1 test_dual_num5 *.o *.s

main_mult_3: main_mult_3.cc dual_num5.hh multiply_3.hh multiply_3.o
	$(CXX) $(CXXFLAGS) -o $@ $< multiply_3.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c $<

test_dual_num1: test_dual_num1.cc dual_num1.hh main.o
	$(CXX) $(CXXFLAGS) -o $@ $< main.o

test_dual_num5: test_dual_num5.cc dual_num5.hh main.o
	$(CXX) $(CXXFLAGS) -o $@ $< main.o

multiply_3.o: multiply_3.cc dual_num1.hh dual_num5.hh
	$(CXX) $(CXXFLAGS) -c $<

multiply_3.s: multiply_3.o
	objdump -d $< > $@

multiply_3_autodiff.o: multiply_3_autodiff.cc dual_num1.hh dual_num5.hh
	$(CXX) $(CXXFLAGS) -c $<

multiply_3_autodiff.s: multiply_3_autodiff.o
	objdump -d $< > $@

main_mult_3.txt: main_mult_3.cc dual_num5.hh
	clang++ $(CXXFLAGS) $(CLANG_DUMP_FLAGS) $< > $@

hideous.o: hideous.cc dual_num5.hh
	$(CXX) $(CXXFLAGS) -c $<

hideous.s: hideous.o
	objdump -d $< > $@

test: test_dual_num1 test_dual_num5
	./test_dual_num1
	./test_dual_num5

