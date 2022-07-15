CXXFLAGS=-O3 -std=c++17 -Wall -Wextra

all: overload overload2
clean:
	rm -f overload overload2 overload3

overload: overload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload2: overload2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload3: overload3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
