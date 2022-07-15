all: overload overload2
clean:
	rm -f overload overload2 overload3

overload: overload.cpp
	$(CXX) -std=c++17 -O3 -o $@ $<

overload2: overload2.cpp
	$(CXX) -std=c++17 -O3 -o $@ $<

overload3: overload3.cpp
	$(CXX) -std=c++17 -O3 -o $@ $<
