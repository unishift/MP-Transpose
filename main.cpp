#include <iostream>
#include <omp.h>

#include "Matrix.h"

/// Performs transposition method from linked library on char matrix<br>
/// Returns time with respect to multi-threading
/// \param src - source matrix
/// \param dst - destination matrix
/// \return elapsed time in seconds
double transpose_test(const Matrix<char>& src, Matrix<char>& dst, size_t num_threads);

int main(int argc, char** argv) {
    // Turn off sync with stdio for performance reasons
    std::ios::sync_with_stdio(false);

    if (argc != 4) {
        std::cout << "Incorrect usage\n"
                  << "\t" << argv[0] << " rows cols num_threads"
                  << std::endl;
        return 1;
    }

    // Get matrix size
    const size_t rows = strtoul(argv[1], nullptr, 10);
    const size_t cols = strtoul(argv[2], nullptr, 10);
    const size_t num_threads = strtoul(argv[3], nullptr, 10);
    if (rows == 0 || cols == 0) {
        std::cout << "Incorrect matrix size" << std::endl;
        return 2;
    }

    // Init matrices
    Matrix<char> mat1(rows, cols);
    Matrix<char> mat2(cols, rows);

    // Transpose block
    const double elapsed_time = transpose_test(mat1, mat2, num_threads);

    // Print data to csv
    // num_threads, rows, cols, elapsed_time
    std::cerr << num_threads << ',' << rows << ',' << cols << ',' << elapsed_time << std::endl;
}
