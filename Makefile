CXXFLAGS=-O3 -std=c++17 -Wall -Wextra

# overload3 is not included in the 'all' target because it does not compile.
# It is an example of one failed attempt to allow an intitial floating-point
# literal in an expression of DualNums.
# To try to build it, use:
#     make overload3

all: overload overload2
clean:
	rm -f overload overload2 overload3

overload: overload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload2: overload2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload3: overload3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
