#include <iostream>
#include <omp.h>

template <typename T>
class Matrix {
    T* ptr;
    size_t _rows;
    size_t _cols;
public:
    Matrix(size_t rows, size_t cols) :
        ptr(new T[rows * cols]),
        _rows(rows), _cols(cols)
    { }

    ~Matrix() {
        delete [] ptr;
    }

    T& operator()(size_t i, size_t j) {
        return ptr[i * _cols + j];
    }

    const T& operator()(size_t i, size_t j) const {
        return ptr[i * _cols + j];
    }

};
