CXX = c++
CXXFLAGS = -O3 -std=c++14 -Wall -Wextra
TEST = test
BENCHMARK = benchmark
TESTSRC = src/test.cpp
BENCHSRC = src/benchmark.cpp
IFLAGS = -I include


all: $(TEST) $(BENCHMARK)

$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST).x $(CXXFLAGS) $(IFLAGS)

$(BENCHMARK): $(BENCHSRC)
	$(CXX) -g $< -o $(BENCHMARK).x $(CXXFLAGS) $(IFLAGS)

clean:
	rm -fr test.x benchmark.x

.PHONY: all clean
