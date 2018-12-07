#include <omp.h>

#include "Matrix.h"


// Implementation of recursive transposition<br>
// Splits until threshold block size reached and then performs transposition of sub-matrix
template <typename T, size_t BLOCK_ROWS, size_t BLOCK_COLS>
void _transpose_recursive(const Matrix<T>& src, Matrix<T>& dst,
                          const size_t i_shift, const size_t j_shift,
                          const size_t rows, const size_t cols) {

    // If sub-matrix is big, divide it on biggest dimension by half
    // Else transpose it
    if (rows > BLOCK_ROWS || cols > BLOCK_COLS) {

        if (rows > cols) {
            const size_t half_rows = rows / 2;
            #pragma omp task shared(src, dst)
            {
                _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst,
                                                                i_shift, j_shift,
                                                                half_rows, cols);
            }
            #pragma omp task shared(src, dst)
            {
                _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst,
                                                                i_shift + half_rows, j_shift,
                                                                rows - half_rows, cols);
            }
        } else {
            const size_t half_cols = cols / 2;
            #pragma omp task shared(src, dst)
            {
                _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst,
                                                                i_shift, j_shift,
                                                                rows, half_cols);
            }
            #pragma omp task shared(src, dst)
            {
                _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst,
                                                                i_shift, j_shift + half_cols,
                                                                rows, cols - half_cols);
            }
        }

    } else {

        // Regular transpose for block
        for (size_t j = j_shift; j < j_shift + cols; j++) {
            for (size_t i = i_shift; i < i_shift + rows; i++) {
                dst(j, i) = src(i, j);
            }
        }

    }
}

// Perform matrix out-place transpose recursive way<br>
// Improved with OpenMP
template <typename T, size_t BLOCK_ROWS = 16, size_t BLOCK_COLS = 16> inline
void transpose_openmp(const Matrix<T>& src, Matrix<T>& dst) {
    #pragma omp parallel
    #pragma omp single
    _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, 0, 0, src.rows(), src.cols());
    #pragma omp taskwait
}

double transpose_test(const Matrix<char>& src, Matrix<char>& dst, size_t num_threads) {
    omp_set_num_threads(num_threads);
    const double start_time = omp_get_wtime();
    transpose_openmp<char, 32, 32>(src, dst);
    const double end_time = omp_get_wtime();

    return end_time - start_time;
}
