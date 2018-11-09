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
    Matrix<char> matrix1(rows, cols);
    Matrix<char> matrix2(cols, rows); //NOLINT

    // Transpose
    const double start_time = omp_get_wtime();
    transpose(matrix1, matrix2);
    const double end_time = omp_get_wtime();

}
