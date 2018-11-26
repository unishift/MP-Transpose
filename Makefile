.PHONY: all clean

all: test_regular test_openmp

clean:
	rm test_regular test_openmp

test_regular: main.cpp transpose_regular.cpp Matrix.h
	${CXX} -std=c++11 -O3 -o test_regular main.cpp transpose_regular.cpp

test_openmp: main.cpp transpose_openmp.cpp Matrix.h
	${CXX} -std=c++11 -O3 -fopenmp -o test_openmp main.cpp transpose_openmp.cpp
