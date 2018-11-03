#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char* ptr;
    size_t rows;
    size_t cols;
} Matrix;


/**
 * Initialize matrix structure
 * @param matrix - Pointer to matrix
 * @param rows - Number of rows
 * @param cols - Number of cols
 * @return 1 with success, 0 with error
 */
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
        fprintf(stderr, "Memory error \n");
        return 1;
    }
    Matrix_new(&matrix2, n_cols, n_rows);
    Matrix_init(&matrix1);


    Matrix_transpose(&matrix1, &matrix2);
}
