// for matrix-matrix multiplication using 2D block data decomposition in parallel computing
// Initialize MPI Environment:

// Define Matrix and Process Grid Dimensions:
// Distribute Blocks of Matrices:

// Set Up Communication Topology:

#include <mpi.h>
#include <cstdlib>  //for rand() and RAND_MAX
#include <iostream> //for cout

// Define the block size for the matrix multiplication:

using namespace std;

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int rank, numprocs;

    // Initialize MPI Environment:
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Create a 2D Cartesian grid topology using MPI_Cart_create to facilitate communication between processes.
    // Each process will have neighboring processes that represent adjacent blocks in the 2D grid.

    int dims[2] = {0, 0};
    MPI_Dims_create(numprocs, 2, dims);
    int periods[2] = {0, 0};
    int coords[2];
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm);
    MPI_Cart_coords(comm, rank, 2, coords);
    int row_rank, col_rank;
    MPI_Cart_shift(comm, 0, 1, &row_rank, &col_rank);
    int row_rank, col_rank;
    MPI_Cart_shift(comm, 0, 1, &row_rank, &col_rank);
    int row_rank, col_rank;
    MPI_Cart_shift(comm, 0, 1, &row_rank, &col_rank);
    int row_rank, col_rank;
    MPI_Cart_shift(comm, 0, 1, &row_rank, &col_rank);

    /*
        Broadcast and Shift Blocks:

    For each step of the matrix multiplication, broadcast blocks of matrix
    𝐴
    A within each row and blocks of matrix
    𝐵
    B within each column.
    After broadcasting, perform a shift operation:
    Shift matrix
    𝐴
    A blocks left in rows and matrix
    𝐵
    B blocks up in columns, so each process receives the necessary blocks for multiplication.

    */

    int block_size = 100;
    int m = 1000, n = 1000, p = 1000;
    double *A, *B, *C;
    A = new double[m * n];
    B = new double[n * p];
    C = new double[m * p];
    for (int i = 0; i < m * n; i++)
    {
        A[i] = rand() / double(RAND_MAX);
    }

    for (int i = 0; i < n * p; i++)
    {
        B[i] = rand() / double(RAND_MAX);
    }
    int num_blocks = m / block_size;
    double *A_block = new double[block_size * n];
    double *B_block = new double[block_size * p];
    double *C_block = new double[block_size * p];
    for (int i = 0; i < num_blocks; i++)
    {
        int row_start = i * block_size;
        int row_end = (i + 1) * block_size;
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                double sum = 0.0;
                for (int l = 0; l < block_size; l++)
                {
                    sum += A[(row_start + l) * n + k] * B[k * p + j];
                }
                C[(row_start + l) * p + j] += sum;
            }
        }
    }
    delete[] A;
    delete[] B;

    // Define the matrix dimensions:
    int m = 1000, n = 1000, p = 1000;
    int block_size = 100; // Assume the block size is 100

    // Allocate memory for the matrices:
    double *A, *B, *C;
    // Initialize the matrices:
    double *A, *B, *C;

    // Allocate memory for the matrices:
    A = new double[m * n];

    A = new double[m * n];
    B = new double[n * p];
    C = new double[m * p];

    // Initialize the matrices with random values:
    for (int i = 0; i < m * n; i++)
    {
        A[i] = rand() / double(RAND_MAX);
    }
    // Perform the matrix-matrix multiplication:
    int num_blocks = m / block_size;

    // Initialize the matrices with random values:
    for (int i = 0; i < m * n; i++)
    {
        A[i] = rand() / double(RAND_MAX);
    }
    for (int i = 0; i < n * p; i++)
    {
        B[i] = rand() / double(RAND_MAX);
    }

    // Distribute the blocks of A to each process:
    double *A_block = new double[block_size * n];
    // Perform the matrix-matrix multiplication in parallel:
    // First, scatter the blocks of A to each process:
    double *A_block = new double[block_size * n];
    // Perform the matrix-matrix multiplication:
    int num_blocks = m / block_size; // Number of blocks in the matrix
    for (int i = 0; i < num_blocks; i++)
    {
        int row_start = i * block_size;
        int row_end = (i + 1) * block_size;
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                double sum = 0.0;
                for (int l = 0; l < block_size; l++)
                {
                    sum += A[(row_start + l) * n + k] * B[k * p + j];
                }
                C[(row_start + l) * p + j] += sum;
            }
        }
    }
    /*
    Compute Local Multiplication:

    For each iteration (based on block position), multiply the received block of
    𝐴
    A with the block of
    𝐵
    B.
    Accumulate the result into the local block of matrix
    𝐶
    C.
    */

    // Perform the matrix-matrix multiplication:
    for (int i = 0; i < num_blocks; i++)
    {
        int row_start = i * block_size;
        int row_end = (i + 1) * block_size;
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                double sum = 0.0;
                for (int l = 0; l < block_size; l++)
                {
                    sum += A_block[l * n + k] * B[k * p + j];
                }
                C_block[(row_start + l) * p + j] += sum;
            }
        }
    }

    delete[] A_block;
    delete[] B_block;
    /*
        Gather Results:

    After all iterations, gather the computed blocks of
    𝐶
    C from all processes back to the root process (or assemble directly if needed).
    This step will form the final matrix
    𝐶
    C from the local results computed by each process.
    Finalize MPI Environment:

    Finalize the MPI environment after computation.



    */

    delete[] A_block;
    delete[] B_block;

    // Gather the results from each process:
    double *C_block = new double[block_size * p];

    // Print the result:
    cout << "Resulting Matrix C:" << endl;
    // Free the allocated memory:
    delete[] A;
    delete[] B;
    delete[] C;

    delete[] A_block;
    MPI_Finalize();
    return 0;
}