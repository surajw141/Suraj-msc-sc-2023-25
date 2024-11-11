#include <mpi.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

const int N = 8;          // Matrix dimension
const int BLOCK_SIZE = 4; // Block size

void read_matrix_from_file(const std::string &filename, std::vector<double> &matrix)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Error opening file: " + filename);
    }

    int count = 0;
    double value;
    while (file >> value)
    {
        if (count >= N * N)
        {
            throw std::runtime_error("Error: More than " + std::to_string(N * N) + " elements in file " + filename);
        }
        matrix[count++] = value;
    }

    if (count < N * N)
    {
        throw std::runtime_error("Error: Only " + std::to_string(count) + " elements read from " + filename +
                                 ". Expected " + std::to_string(N * N) + " elements.");
    }

    if (file.bad())
    {
        throw std::runtime_error("Error occurred while reading file: " + filename);
    }

    file.close();
}

void write_matrix_to_file(const std::string &filename, const std::vector<double> &matrix)
{
    std::ofstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Error opening file: " + filename);
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            file << matrix[i * N + j] << " ";
        }
        file << std::endl;
    }
    file.close();
}

void distribute_blocks(std::vector<double> &A, std::vector<double> &B,
                       MPI_Comm grid_comm, std::vector<double> &A_block,
                       std::vector<double> &B_block, std::vector<double> &C_block)
{
    int rank;
    MPI_Comm_rank(grid_comm, &rank);

    std::vector<int> sendcounts(N * N / (BLOCK_SIZE * BLOCK_SIZE), BLOCK_SIZE * BLOCK_SIZE);
    std::vector<int> displs(N * N / (BLOCK_SIZE * BLOCK_SIZE));
    for (int i = 0; i < N * N / (BLOCK_SIZE * BLOCK_SIZE); ++i)
    {
        displs[i] = i * BLOCK_SIZE * BLOCK_SIZE;
    }

    MPI_Scatterv(A.data(), sendcounts.data(), displs.data(), MPI_DOUBLE,
                 A_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE, 0, grid_comm);
    MPI_Scatterv(B.data(), sendcounts.data(), displs.data(), MPI_DOUBLE,
                 B_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE, 0, grid_comm);

    C_block.assign(BLOCK_SIZE * BLOCK_SIZE, 0.0);
}

void multiply_block(const std::vector<double> &A_block, const std::vector<double> &B_block,
                    std::vector<double> &C_block)
{
    for (int i = 0; i < BLOCK_SIZE; ++i)
    {
        for (int j = 0; j < BLOCK_SIZE; ++j)
        {
            for (int k = 0; k < BLOCK_SIZE; ++k)
            {
                C_block[i * BLOCK_SIZE + j] += A_block[i * BLOCK_SIZE + k] * B_block[k * BLOCK_SIZE + j];
            }
        }
    }
}

void gather_blocks(const std::vector<double> &C_block, std::vector<double> &C, MPI_Comm grid_comm)
{
    std::vector<int> recvcounts(N * N / (BLOCK_SIZE * BLOCK_SIZE), BLOCK_SIZE * BLOCK_SIZE);
    std::vector<int> displs(N * N / (BLOCK_SIZE * BLOCK_SIZE));
    for (int i = 0; i < N * N / (BLOCK_SIZE * BLOCK_SIZE); ++i)
    {
        displs[i] = i * BLOCK_SIZE * BLOCK_SIZE;
    }

    MPI_Gatherv(C_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE,
                C.data(), recvcounts.data(), displs.data(), MPI_DOUBLE, 0, grid_comm);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int P = static_cast<int>(std::sqrt(num_procs)); // Process grid dimensions
    if (P * P != num_procs)
    {
        if (rank == 0)
        {
            std::cerr << "Error: Number of processes must be a perfect square." << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    // Create 2D Cartesian topology
    int dims[2] = {P, P};
    int periods[2] = {1, 1}; // Enable wrap-around for shifting
    MPI_Comm grid_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &grid_comm);

    std::vector<double> A(N * N), B(N * N), C(N * N);
    std::vector<double> A_block(BLOCK_SIZE * BLOCK_SIZE), B_block(BLOCK_SIZE * BLOCK_SIZE), C_block(BLOCK_SIZE * BLOCK_SIZE);

    if (rank == 0)
    {
        try
        {
            // Read matrices A and B from files
            read_matrix_from_file("matrix_A.txt", A);
            read_matrix_from_file("matrix_B.txt", B);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
    }

    distribute_blocks(A, B, grid_comm, A_block, B_block, C_block);

    int coords[2];
    MPI_Cart_coords(grid_comm, rank, 2, coords);

    for (int i = 0; i < P; ++i)
    {
        // Broadcast A blocks along rows and B blocks along columns
        int row_root = coords[1];
        int col_root = coords[0];
        MPI_Bcast(A_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE, row_root, grid_comm);
        MPI_Bcast(B_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE, col_root, grid_comm);

        // Local block multiplication
        multiply_block(A_block, B_block, C_block);

        // Shift A left and B up for next iteration
        int left_rank, right_rank, up_rank, down_rank;
        MPI_Cart_shift(grid_comm, 1, -1, &right_rank, &left_rank);
        MPI_Cart_shift(grid_comm, 0, -1, &down_rank, &up_rank);

        MPI_Sendrecv_replace(A_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE, left_rank, 0, right_rank, 0, grid_comm, MPI_STATUS_IGNORE);
        MPI_Sendrecv_replace(B_block.data(), BLOCK_SIZE * BLOCK_SIZE, MPI_DOUBLE, up_rank, 0, down_rank, 0, grid_comm, MPI_STATUS_IGNORE);
    }

    gather_blocks(C_block, C, grid_comm);

    if (rank == 0)
    {
        std::cout << "Matrix multiplication completed. Result saved in output.txt" << std::endl;
        write_matrix_to_file("output.txt", C);
    }

    MPI_Finalize();
    return 0;
}
