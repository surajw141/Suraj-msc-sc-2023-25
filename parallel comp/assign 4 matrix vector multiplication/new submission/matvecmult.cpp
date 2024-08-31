#include <mpi.h>
#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = size;  // Number of rows (and columns) of the matrix
    std::vector<double> A(n);  // Matrix row
    double x_element;          // Element of vector x corresponding to the rank
    double y_element = 0.0;    // Result element of vector y for this rank

    std::vector<double> full_A;
    std::vector<double> x(n);
    std::vector<double> y(n);

    if (rank == 0) {
        // Read matrix and vector from file
        std::ifstream infile("matrix_vector_input.txt");
        if (!infile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        infile >> n;
        full_A.resize(n * n);
        x.resize(n);
        y.resize(n);

        for (int i = 0; i < n * n; ++i) {
            infile >> full_A[i];
        }

        for (int i = 0; i < n; ++i) {
            infile >> x[i];
        }

        infile.close();
    }

    // Broadcast the value of n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Resize vectors on all processes after receiving the value of n
    A.resize(n);
    if (rank != 0) {
        x.resize(n);
        y.resize(n);
    }

    // Scatter the rows of matrix A to all processes
    MPI_Scatter(full_A.data(), n, MPI_DOUBLE, A.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter the elements of vector x to all processes
    MPI_Scatter(x.data(), 1, MPI_DOUBLE, &x_element, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Each process computes its corresponding element of y
    for (int i = 0; i < n; ++i) {
        y_element += A[i] * x_element;
    }

    // Gather the result vector y on rank 0
    MPI_Gather(&y_element, 1, MPI_DOUBLE, y.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Rank 0 prints the result
    if (rank == 0) {
        std::cout << "Result vector y:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << y[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}

