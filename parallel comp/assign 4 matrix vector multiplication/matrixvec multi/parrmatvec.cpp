#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <mpi.h>

using namespace std;

//read matrix from file
void read_matrix(const char* filename, vector<vector<double>>& matrix, int& m, int& n) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening matrix file." << endl;
        exit(1);
    }

    infile >> m >> n;
    matrix.resize(m, vector<double>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> matrix[i][j];
        }
    }
    infile.close();
}

// Function to read vector from file
void read_vector(const char* filename, vector<double>& vec, int& n) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening vector file." << endl;
        exit(1);
    }

    infile >> n;
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        infile >> vec[i];
    }
    infile.close();
}

// Function to perform matrix-vector multiplication on a subset of rows
void multiply_matrix_vector(const vector<double>& matrix, const vector<double>& vec, vector<double>& result, int start_row, int end_row, int n) {
    for (int i = start_row; i < end_row; ++i) {
        result[i - start_row] = 0.0;
        for (int j = 0; j < n; ++j) {
            result[i - start_row] += matrix[i * n + j] * vec[j];
        }
    }
}

int main(int argc, char* argv[]) {
    int id, p;
    vector<vector<double>> matrix;
    vector<double> vec;
    int m, n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (id == 0) {
        // Master process reads matrix and vector from files
        read_matrix("matrix.txt", matrix, m, n);
        read_vector("vector.txt", vec, n);
    }

    // Broadcast the matrix dimensions and vector
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    vec.resize(n);
    MPI_Bcast(vec.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Flatten the matrix for scattering
    vector<double> flattened_matrix;
    if (id == 0) {
        flattened_matrix.resize(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                flattened_matrix[i * n + j] = matrix[i][j];
            }
        }
    }

    // Scatter the rows of the matrix to all processes
    int rows_per_process = m / p;
    vector<double> local_matrix_rows(rows_per_process * n);
    vector<double> local_result(rows_per_process);

    MPI_Scatter(flattened_matrix.data(), rows_per_process * n, MPI_DOUBLE, 
                local_matrix_rows.data(), rows_per_process * n, MPI_DOUBLE, 
                0, MPI_COMM_WORLD);

    // Perform local matrix-vector multiplication
    multiply_matrix_vector(local_matrix_rows, vec, local_result, 0, rows_per_process, n);

    // Gather the results back to the master process
    vector<double> result(m);
    MPI_Gather(local_result.data(), rows_per_process, MPI_DOUBLE, 
               result.data(), rows_per_process, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);

    if (id == 0) {
        // Print the result
        cout << "\nMatrix-Vector Product:\n";
        for (int i = 0; i < m; ++i) {
            cout << setw(4) << i << "  " << setw(10) << result[i] << "\n";
        }
    }

    MPI_Finalize();
    return 0;
}
