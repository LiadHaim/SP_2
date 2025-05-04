# liadi.haim@gmail.com

CXX       := clang++
CXXFLAGS  := -std=c++17 -Wall -Wextra -g

.PHONY: all test run_main run_tests valgrind clean

all: main Test

main: main.o SquareMat.o
	$(CXX) $(CXXFLAGS) -o $@ $^

Test: Test.o SquareMat.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Test.o: Test.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

SquareMat.o: SquareMat.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Main: main
	./main

test: Test
	./Test

valgrind: main
	valgrind --leak-check=full ./main

clean:
	rm -f *.o main Test
