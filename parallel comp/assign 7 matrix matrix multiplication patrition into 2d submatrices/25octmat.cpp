#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath> // Include this for sqrt function

#define N 4 // Matrix dimensions (modify as needed)

void matrixMultiply(const double *A, const double *B, double *C, int local_size)
{
    for (int i = 0; i < local_size; ++i)
    {
        for (int j = 0; j < local_size; ++j)
        {
            C[i * local_size + j] = 0.0;
            for (int k = 0; k < local_size; ++k)
            {
                C[i * local_size + j] += A[i * local_size + k] * B[k * local_size + j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sqrt_size = (int)std::sqrt(size); // Number of rows and cols of processors
    if (sqrt_size * sqrt_size != size)
    {
        if (rank == 0)
        {
            std::cerr << "The number of processes must be a perfect square." << std::endl;
        }
        MPI_Finalize();
        return -1;
    }

    int local_size = N / sqrt_size; // Local matrix size per process

    // Allocate matrices for each process
    std::vector<double> A(local_size * local_size, 1.0);
    std::vector<double> B(local_size * local_size, 1.0);
    std::vector<double> C(local_size * local_size, 0.0);

    MPI_Comm row_comm, col_comm;
    int row_rank, col_rank;

    // Create row and column communicators
    MPI_Comm_split(MPI_COMM_WORLD, rank / sqrt_size, rank, &row_comm);
    MPI_Comm_split(MPI_COMM_WORLD, rank % sqrt_size, rank, &col_comm);

    MPI_Comm_rank(row_comm, &row_rank);
    MPI_Comm_rank(col_comm, &col_rank);

    // Broadcast along rows and columns
    MPI_Bcast(A.data(), local_size * local_size, MPI_DOUBLE, 0, row_comm);
    MPI_Bcast(B.data(), local_size * local_size, MPI_DOUBLE, 0, col_comm);

    // Perform local matrix multiplication
    matrixMultiply(A.data(), B.data(), C.data(), local_size);

    // Gather the results at the root process
    std::vector<double> final_matrix;
    if (rank == 0)
    {
        final_matrix.resize(N * N, 0.0);
    }

    MPI_Gather(C.data(), local_size * local_size, MPI_DOUBLE,
               final_matrix.data(), local_size * local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Print the result if rank 0
    if (rank == 0)
    {
        std::cout << "Result Matrix C:\n";
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                std::cout << final_matrix[i * N + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Free communicators
    MPI_Comm_free(&row_comm);
    MPI_Comm_free(&col_comm);

    MPI_Finalize();
    return 0;
}
