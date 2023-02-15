CXX=g++-12
CXXFLAGS=-O3 -std=c++17 -Wall -Wextra -mfma

.PHONY: test

all:  test_dual_num2 multiply_3.s

clean:
	rm -f overload test_dual_num2 main.o multiply_3.o multiply_3.s

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c $<

test_dual_num2: test_dual_num1.cc dual_num1.hh main.o
	$(CXX) $(CXXFLAGS) -o $@ $< main.o

multiply_3.o: multiply_3.cc dual_num1.hh dual_num5.hh
	$(CXX) $(CXXFLAGS) -c $<

multiply_3.s: multiply_3.o
	objdump -d $< > $@

test: test_dual_num2
	./test_dual_num2

