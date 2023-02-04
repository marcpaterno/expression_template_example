#CXX=g++-12
CXXFLAGS=-O3 -std=c++17 -Wall -Wextra

.PHONY: test

all: overload overload2

clean:
	rm -f overload overload2 main.o

overload: overload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c $<

overload2: overload2.cpp dual_num2.hpp main.o
	$(CXX) $(CXXFLAGS) -o $@ $< main.o

test: overload2
	./overload2

