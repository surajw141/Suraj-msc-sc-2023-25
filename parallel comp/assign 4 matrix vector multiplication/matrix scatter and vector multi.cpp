#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 4;  // Matrix dimensions
    int A[N][N] = {   // 4x4 matrix
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int x[N] = {1, 2, 3, 4};  // Vector x
    int local_column[N];      // To store the column assigned to each processor
    int local_result = 0;     // Local computation of z[i]

    // Scatter columns of A to each processor
    MPI_Scatter(A, N, MPI_INT, local_column, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local computation: z[i] = column[i] * x[i]
    for (int i = 0; i < N; ++i) {
        local_result += local_column[i] * x[rank];
    }

    // Gather results on rank 0
    std::vector<int> results(size);
    MPI_Gather(&local_result, 1, MPI_INT, results.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Print results on rank 0
    if (rank == 0) {
        std::cout << "Result vector z: [ ";
        for (int i = 0; i < size; ++i) {
            std::cout << results[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    MPI_Finalize();
    return 0;
}

