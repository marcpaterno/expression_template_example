#CXX=g++-12
CXXFLAGS=-O3 -std=c++17 -Wall -Wextra

.PHONY: test

all:  test_dual_num2

clean:
	rm -f overload test_dual_num2 main.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c $<

test_dual_num2: test_dual_num1.cc dual_num1.hh main.o
	$(CXX) $(CXXFLAGS) -o $@ $< main.o

test: test_dual_num2
	./test_dual_num2

