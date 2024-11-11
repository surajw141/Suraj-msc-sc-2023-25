#include <mpi.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

const int N = 4; // Number of equations (and rows in matrix A)

void printMatrix(const std::vector<std::vector<double>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (double val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void readMatrixAndVectorFromFile(const std::string &filename, std::vector<std::vector<double>> &A, std::vector<double> &b)
{
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inputFile >> A[i][j];
        }
        inputFile >> b[i];
    }

    inputFile.close();
}

void writeSolutionToFile(const std::string &filename, const std::vector<double> &x)
{
    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    outputFile << "Solution:" << std::endl;
    for (double val : x)
    {
        outputFile << val << " ";
    }
    outputFile << std::endl;

    outputFile.close();
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define matrix A and vector b
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<double> b(N);

    if (rank == 0)
    {
        // Read A and b from file
        readMatrixAndVectorFromFile("input.txt", A, b);

        std::cout << "Initial Matrix A:" << std::endl;
        printMatrix(A);
        std::cout << "Initial Vector b:" << std::endl;
        for (double val : b)
            std::cout << val << " ";
        std::cout << std::endl;
    }

    // Broadcast A and b to all processors
    for (int i = 0; i < N; i++)
    {
        MPI_Bcast(A[i].data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    MPI_Bcast(b.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Forward elimination
    for (int pivot_row = 0; pivot_row < N; pivot_row++)
    {
        int owner = pivot_row % size;

        if (rank == owner)
        {
            // Normalize the pivot row
            double pivot = A[pivot_row][pivot_row];
            for (int j = pivot_row; j < N; j++)
            {
                A[pivot_row][j] /= pivot;
            }
            b[pivot_row] /= pivot;
        }

        // Broadcast the pivot row
        MPI_Bcast(A[pivot_row].data(), N, MPI_DOUBLE, owner, MPI_COMM_WORLD);
        MPI_Bcast(&b[pivot_row], 1, MPI_DOUBLE, owner, MPI_COMM_WORLD);

        // Eliminate in rows owned by this processor
        for (int i = pivot_row + 1 + rank; i < N; i += size)
        {
            double factor = A[i][pivot_row];
            for (int j = pivot_row; j < N; j++)
            {
                A[i][j] -= factor * A[pivot_row][j];
            }
            b[i] -= factor * b[pivot_row];
        }
    }

    // Back substitution
    std::vector<double> x(N);
    for (int i = N - 1; i >= 0; i--)
    {
        int owner = i % size;
        if (rank == owner)
        {
            x[i] = b[i];
            for (int j = i + 1; j < N; j++)
            {
                x[i] -= A[i][j] * x[j];
            }
        }
        MPI_Bcast(&x[i], 1, MPI_DOUBLE, owner, MPI_COMM_WORLD);
    }

    // Root processor writes the solution to the output file
    if (rank == 0)
    {
        writeSolutionToFile("output.txt", x);
    }

    MPI_Finalize();
    return 0;
}
