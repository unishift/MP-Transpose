.PHONY: all clean

all: test_regular test_openmp test_mpi

clean:
	rm *.o test_regular test_openmp test_mpi

main.o: main.cpp Matrix.h
	${CXX} -O3 -c main.cpp

transpose_regular.o: transpose_regular.cpp Matrix.h
	${CXX} -O3 -c transpose_regular.cpp

transpose_openmp.o: transpose_openmp.cpp Matrix.h
	${CXX} -O3 -fopenmp -c transpose_openmp.cpp

transpose_mpi.o: transpose_mpi.cpp Matrix.h
	${CXX} -O3 -c transpose_mpi.cpp

test_regular: main.o transpose_regular.o
	${CXX} -O3 -o test_regular main.o transpose_regular.o

test_openmp: main.o transpose_openmp.o
	${CXX} -O3 -fopenmp -o test_openmp main.o transpose_openmp.o

test_mpi: main.o transpose_mpi.o
	mpic++ -O3 -lmpi -o test_mpi main.o transpose_mpi.o
