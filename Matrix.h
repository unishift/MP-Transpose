#include <cstddef>

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


    /// Perform matrix out-place transpose regular way
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

    friend
    bool operator==(const Matrix& mat1, const Matrix& mat2) {
        for (size_t i = 0; i < mat1.rows(); i++) {
            for (size_t j = 0; j < mat1.cols(); j++) {
                if (mat1(i, j) != mat2(i, j)) return false;
            }
        }
        return true;
    }
};

