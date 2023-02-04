CXXFLAGS=-O3 -std=c++17 -Wall -Wextra

# overload3 is not included in the 'all' target because it does not compile.
# To try to build it, use:
#     make overload3

all: overload overload2
clean:
	rm -f overload overload2 overload3

overload: overload.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload2: overload2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

overload3: overload3.cpp dual_num3.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<
