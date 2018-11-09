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

};
