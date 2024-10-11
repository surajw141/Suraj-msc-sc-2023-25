#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

void multiply_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 8; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}






int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int m = 8, n = 8, p = 8;
    vector<vector<int>> A(m, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(p));
    vector<vector<int>> C(m, vector<int>(p, 0));

    if (rank == 0) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = i + j;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < p; j++)
                B[i][j] = i + j;
    }

    int rows_per_process = 4;
    vector<int> local_A(rows_per_process * n);
    MPI_Scatter(&A[0][0], rows_per_process * n, MPI_INT, &local_A[0], rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    vector<vector<int>> local_A_matrix(rows_per_process, vector<int>(n));
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < n; j++) {
            local_A_matrix[i][j] = local_A[i * n + j];
        }
    }

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(&B[0][0], n * p, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&B[0][0], n * p, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }




























    vector<vector<int>> local_C(rows_per_process, vector<int>(p, 0));
    multiply_matrices(local_A_matrix, B, local_C);

    MPI_Gather(&local_C[0][0], rows_per_process * p, MPI_INT, &C[0][0], rows_per_process * p, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Resulting Matrix C:" << endl;
        for (const auto& row : C) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
