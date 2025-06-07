#ronamsalem4@gmail.com 
# This Makefile compiles and runs the main demo (main.cpp), the unit tests (test.cpp),
# checks for memory leaks using valgrind, and cleans up temporary files.
# Targets: Main, test, valgrind, clean
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror


MAIN = main.cpp
TEST = test.cpp
HDR = MyContainer.hpp
LIBS = doctest.h


all: Main


Main: $(MAIN) $(HDR)
	$(CXX) $(CXXFLAGS) -o main $(MAIN)
	./main


test: $(TEST) $(HDR) $(LIBS)
	$(CXX) $(CXXFLAGS) -o test $(TEST)
	./test


valgrind:
	valgrind --leak-check=full ./test
	valgrind --leak-check=full ./main

clean:
	rm -f main test *.o *.out 
