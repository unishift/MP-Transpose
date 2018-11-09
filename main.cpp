#include <iostream>
#include <omp.h>

#include "Matrix.h"

int main(int argc, char** argv) {
    // Turn off sync with stdio for performance reasons
    std::ios::sync_with_stdio(false);

    if (argc != 3) {
        std::cerr << "Incorrect usage\n"
                  << "\t" << argv[0] << " rows cols"
                  << std::endl;
        return 1;
    }

    // Get matrix size
    const size_t rows = strtoul(argv[1], nullptr, 10);
    const size_t cols = strtoul(argv[2], nullptr, 10);
    if (rows == 0 || cols == 0) {
        std::cerr << "Incorrect matrix size" << std::endl;
        return 2;
    }

    // Init matrices
    Matrix<char> mat1(rows, cols);
    Matrix<char> mat2(cols, rows); //NOLINT

    double start_time;
    double end_time;

    // Transpose block
    start_time = omp_get_wtime();
    transpose_recursive<char>(mat1, mat2);
    end_time = omp_get_wtime();
    std::cout << end_time - start_time << std::endl;
}
