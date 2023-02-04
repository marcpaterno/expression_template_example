CXXFLAGS=-O3 -std=c++17 -Wall -Wextra

all: overload overload2
clean:
	rm -f overload overload2

overload: overload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload2: overload2.cpp dual_num2.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<
