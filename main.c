#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char* ptr;
    size_t rows;
    size_t cols;
} Matrix;


int Matrix_new(Matrix* matrix, size_t rows, size_t cols) {
    if (matrix == NULL) {
        return 0;
    }

    matrix->ptr = calloc(sizeof(char), rows * cols);
    if (matrix->ptr == NULL) {
        return 0;
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return 1;
}

inline static
void swap(double* x, double* y) {
    double tmp = *x;
    *x = *y;
    *y = tmp;
}

void Matrix_transpose(const Matrix* restrict src, const Matrix* restrict dst) {
    for (int i = 0; i < src->rows; i++) {
        for (int j = 0; j < src->cols; j++) {
            dst->ptr[j * dst->cols + i] = src->ptr[i * src->cols + j];
        }
    }
}

#define I_BLOCK_SIZE 32
#define J_BLOCK_SIZE 32
void Matrix_transpose_rec(const Matrix* restrict src, const Matrix* restrict dst,
                          size_t i_shift, size_t j_shift, size_t rows, size_t cols) {
    if (rows > I_BLOCK_SIZE) {
        const size_t half_rows = rows / 2;
        Matrix_transpose_rec(src, dst, i_shift, j_shift, half_rows, cols);
        Matrix_transpose_rec(src, dst, i_shift + half_rows, j_shift, rows - half_rows, cols);
    } else if (cols > J_BLOCK_SIZE) {
        const size_t half_cols = cols / 2;
        Matrix_transpose_rec(src, dst, i_shift, j_shift, rows, half_cols);
        Matrix_transpose_rec(src, dst, i_shift, j_shift + half_cols, rows, cols - half_cols);
    } else {

        for (int i = i_shift; i < i_shift + rows; i++) {
            for (int j = j_shift; j < j_shift + cols; j++) {
                dst->ptr[j * dst->cols + i] = src->ptr[i * src->cols + j];
            }
        }

    }
}

inline
void Matrix_transpose_fast(const Matrix* restrict src, const Matrix* restrict dst) {
    Matrix_transpose_rec(src, dst, 0, 0, src->rows, src->cols);
}

void Matrix_init(Matrix* const mat) {
    srand(time(NULL));
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->ptr[i * mat->cols + j] = (char) ((rand() - RAND_MAX / 2) % 256);
        }
    }
}

void Matrix_print(const Matrix* const mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d ", (int)mat->ptr[i * mat->cols + j]);
        }
        putchar('\n');
    }
}

int main(int argc, char** argv) {
    size_t n_rows = atoi(argv[1]);
    size_t n_cols = atoi(argv[2]);

    Matrix matrix1;
    Matrix matrix2;
    int err = Matrix_new(&matrix1, n_rows, n_cols);
    if (err == 0) {
        perror("Matrix_new: ");
        return 1;
    }
    Matrix_new(&matrix2, n_cols, n_rows);
    Matrix_init(&matrix1);

    Matrix_transpose_fast(&matrix1, &matrix2);
}
