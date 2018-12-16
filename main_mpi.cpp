#include <iostream>
#include <mpi.h>

#include "Matrix.h"

// Performs transposition method from linked library on char matrix
// Returns time with respect to multi-threading
double transpose_test(const Matrix<char>& src, Matrix<char>& dst, size_t num_threads);

int main(int argc, char** argv) {
    MPI::Init(argc, argv);
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

    // Get number of processes and rank
    const int num_proc = MPI::COMM_WORLD.Get_size();
    const int rank = MPI::COMM_WORLD.Get_rank();

    // Divide matrix evenly per every process
    size_t local_rows = rows;
    size_t local_cols = cols;
    if (rows > cols) {
        local_rows = rows / num_proc;
        if (rank == num_proc - 1) {
            local_rows = rows - local_rows * rank;
        }
    } else {
        local_cols = cols / num_proc;
        if (rank == num_proc - 1) {
            local_cols = cols - local_cols * rank;
        }
    }

    // Init matrices
    Matrix<char> mat1(local_rows, local_cols);
    Matrix<char> mat2(local_cols, local_rows);

    // Transpose block
    const double elapsed_time = transpose_test(mat1, mat2, num_threads);

    // Print data to csv
    // num_threads, rows, cols, elapsed_time
    if (rank == 0) {
        std::cerr << num_threads << ',' << rows << ',' << cols << ',' << elapsed_time << std::endl;
    }
    MPI::Finalize();
}
