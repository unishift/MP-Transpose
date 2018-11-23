#include <ctime>

#include "Matrix.h"


/// Implementation of recursive transposition<br>
/// Performs transposition of sub-matrix
/// \tparam T - matrix inner type
/// \tparam BLOCK_ROWS - maximum rows in block
/// \tparam BLOCK_COLS - maximum columns in block
/// \param src - source matrix
/// \param dst - destination matrix
/// \param i_shift - first row for sub-matrix
/// \param j_shift - first column for sub-matrix
/// \param rows - rows in sub-matrix
/// \param cols - columns in sub-matrix
template <typename T, size_t BLOCK_ROWS, size_t BLOCK_COLS>
void _transpose_recursive(const Matrix<T>& src, Matrix<T>& dst,
                          const size_t i_shift, const size_t j_shift,
                          const size_t rows, const size_t cols) {

    // If sub-matrix is big, divide it on biggest dimension by half
    // Else transpose it
    if (rows > BLOCK_ROWS || cols > BLOCK_COLS) {

        if (rows > cols) {
            const size_t half_rows = rows / 2;
            _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, i_shift, j_shift, half_rows, cols);
            _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, i_shift + half_rows, j_shift, rows - half_rows, cols);
        } else {
            const size_t half_cols = cols / 2;
            _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, i_shift, j_shift, rows, half_cols);
            _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, i_shift, j_shift + half_cols, rows, cols - half_cols);
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

/// Perform matrix out-place transpose recursive way<br>
/// More cache-friendly compared to regular
/// \tparam T - matrix inner type
/// \tparam BLOCK_ROWS - maximum rows in block
/// \tparam BLOCK_COLS - maximum columns in block
/// \param src - source matrix
/// \param dst - destination matrix
template <typename T, size_t BLOCK_ROWS = 16, size_t BLOCK_COLS = 16> inline
void transpose_recursive(const Matrix<T>& src, Matrix<T>& dst) {
    _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, 0, 0, src.rows(), src.cols());
}

double transpose_test(const Matrix<char>& src, Matrix<char>& dst, size_t num_threads) {
    const auto start_clock = clock();
    transpose_recursive<char, 16, 16>(src, dst);
    const auto end_clock = clock();

    return double(end_clock - start_clock) / CLOCKS_PER_SEC;
}

