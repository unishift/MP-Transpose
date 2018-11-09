/// Class for matrix representation<br>
/// It have immutable sizes for performance reasons
/// \tparam T - any type numeric type
template <typename T>
class Matrix {
    T* ptr;
    size_t _rows;
    size_t _cols;
public:
    T& operator()(size_t i, size_t j) {
        return ptr[i * _cols + j];
    }

    const T& operator()(size_t i, size_t j) const {
        return ptr[i * _cols + j];
    }

    /// Initialize matrix with i-j values, where i is row and j is column
    /// \param rows - any positive integer
    /// \param cols - any positive integer
    Matrix(size_t rows, size_t cols) :
        ptr(new T[rows * cols]),
        _rows(rows), _cols(cols) {
    
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*this)(i, j) = i - j;
            }
        }
    }

    ~Matrix() {
        delete [] ptr;
    }

    size_t rows() const {
        return _rows;
    }

    size_t cols() const {
        return _cols;
    }


    /// Perform matrix out-place transpose regular way<br>
    /// \param src - source matrix
    /// \param dst - destination matrix
    friend
    void transpose(const Matrix<T>& src, Matrix<T>& dst) {
        for (int j = 0; j < src.cols(); j++) {
            for (int i = 0; i < src.rows(); i++) {
                dst(j, i) = src(i, j);
            }
        }
    }

};

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

template <typename T, size_t BLOCK_ROWS = 16, size_t BLOCK_COLS = 16> inline
void transpose_recursive(const Matrix<T>& src, Matrix<T>& dst) {
    _transpose_recursive<T, BLOCK_ROWS, BLOCK_COLS>(src, dst, 0, 0, src.rows(), src.cols());
}
