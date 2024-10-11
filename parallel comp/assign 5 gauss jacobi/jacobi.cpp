#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <mpi.h>
#include <memory>

#define MAX_ITERATIONS 100

class Matrix {
public:
    Matrix(int size) : size(size), data(size, std::vector<double>(size)) {}

    double& at(int row, int col) {
        return data[row][col];
    }

    const double& at(int row, int col) const {
        return data[row][col];
    }

    int getSize() const {
        return size;
    }

private:
    int size;
    std::vector<std::vector<double>> data;
};

class Vector {
public:
    Vector(int size) : size(size), data(size) {}

    double& operator[](int index) {
        return data[index];
    }

    const double& operator[](int index) const {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    // Provide access to raw data for MPI operations
    double* dataPtr() {
        return data.data();
    }

    const double* dataPtr() const {
        return data.data();
    }

private:
    int size;
    std::vector<double> data;
};

double Distance(const Vector& X_Old, const Vector& X_New) {
    double sum = 0.0;
    int size = X_Old.getSize();
    for (int i = 0; i < size; ++i) {
        double diff = X_New[i] - X_Old[i];
        sum += diff * diff;
    }
    return sum;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int n_size, NoofRows_Bloc, NoofRows, NoofCols;
    int Numprocs, MyRank, Root = 0;
    int irow, icol, index, Iteration, GlobalRowNo;

    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

    std::unique_ptr<Matrix> Matrix_A;
    std::unique_ptr<Vector> Input_A;
    std::unique_ptr<Vector> Input_B;
    std::unique_ptr<Vector> ARecv;
    std::unique_ptr<Vector> BRecv;
    std::unique_ptr<Vector> X_New;
    std::unique_ptr<Vector> X_Old;
    std::unique_ptr<Vector> Bloc_X;

    if (MyRank == Root) {
        std::ifstream matrixFile("mdatjac.inp");
        if (!matrixFile) {
            std::cerr << "Can't open input matrix file" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        matrixFile >> NoofRows >> NoofCols;
        n_size = NoofRows;

        Matrix_A = std::make_unique<Matrix>(n_size);

        for (irow = 0; irow < n_size; ++irow) {
            for (icol = 0; icol < n_size; ++icol) {
                matrixFile >> Matrix_A->at(irow, icol);
            }
        }
        matrixFile.close();

        std::ifstream vectorFile("vdatjac.inp");
        if (!vectorFile) {
            std::cerr << "Can't open input vector file" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        vectorFile >> NoofRows;
        n_size = NoofRows;

        Input_B = std::make_unique<Vector>(n_size);
        for (irow = 0; irow < n_size; ++irow) {
            vectorFile >> (*Input_B)[irow];
        }
        vectorFile.close();

        Input_A = std::make_unique<Vector>(n_size * n_size);
        index = 0;
        for (irow = 0; irow < n_size; ++irow) {
            for (icol = 0; icol < n_size; ++icol) {
                (*Input_A)[index++] = Matrix_A->at(irow, icol);
            }
        }
    }

    MPI_Bcast(&NoofRows, 1, MPI_INT, Root, MPI_COMM_WORLD);
    MPI_Bcast(&NoofCols, 1, MPI_INT, Root, MPI_COMM_WORLD);

    if (NoofRows != NoofCols) {
        if (MyRank == 0) {
            std::cerr << "Input Matrix Should Be Square Matrix" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    MPI_Bcast(&n_size, 1, MPI_INT, Root, MPI_COMM_WORLD);

    if (n_size % Numprocs != 0) {
        if (MyRank == 0) {
            std::cerr << "Matrix Cannot be Striped Evenly" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    NoofRows_Bloc = n_size / Numprocs;

    ARecv = std::make_unique<Vector>(NoofRows_Bloc * n_size);
    BRecv = std::make_unique<Vector>(NoofRows_Bloc);

    // Debugging prints
    std::cout << "Process " << MyRank << ": Allocated vectors." << std::endl;

    MPI_Scatter(Input_A->dataPtr(), NoofRows_Bloc * n_size, MPI_DOUBLE, ARecv->dataPtr(), NoofRows_Bloc * n_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(Input_B->dataPtr(), NoofRows_Bloc, MPI_DOUBLE, BRecv->dataPtr(), NoofRows_Bloc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    X_New = std::make_unique<Vector>(n_size);
    X_Old = std::make_unique<Vector>(n_size);
    Bloc_X = std::make_unique<Vector>(NoofRows_Bloc);

    for (irow = 0; irow < NoofRows_Bloc; ++irow) {
        (*Bloc_X)[irow] = (*BRecv)[irow];
    }

    MPI_Allgather(Bloc_X->dataPtr(), NoofRows_Bloc, MPI_DOUBLE, X_New->dataPtr(), NoofRows_Bloc, MPI_DOUBLE, MPI_COMM_WORLD);

    Iteration = 0;
    do {
        for (irow = 0; irow < n_size; ++irow) {
            (*X_Old)[irow] = (*X_New)[irow];
        }

        for (irow = 0; irow < NoofRows_Bloc; ++irow) {
            GlobalRowNo = (MyRank * NoofRows_Bloc) + irow;
            (*Bloc_X)[irow] = (*BRecv)[irow];
            index = irow * n_size;

            for (icol = 0; icol < GlobalRowNo; ++icol) {
                (*Bloc_X)[irow] -= (*X_Old)[icol] * (*ARecv)[index + icol];
            }
            for (icol = GlobalRowNo + 1; icol < n_size; ++icol) {
                (*Bloc_X)[irow] -= (*X_Old)[icol] * (*ARecv)[index + icol];
            }
            (*Bloc_X)[irow] /= (*ARecv)[irow * n_size + GlobalRowNo];
        }

        MPI_Allgather(Bloc_X->dataPtr(), NoofRows_Bloc, MPI_DOUBLE, X_New->dataPtr(), NoofRows_Bloc, MPI_DOUBLE, MPI_COMM_WORLD);
        ++Iteration;
        std::cout << "Process " << MyRank << ": Iteration " << Iteration << std::endl;
    } while ((Iteration < MAX_ITERATIONS) && (Distance(*X_Old, *X_New) >= 1.0E-24));

    if (MyRank == 0) {
        std::cout << "\n";
        std::cout << " ------------------------------------------- \n";
        std::cout << "Results of Jacobi Method:\n";
        for (irow = 0; irow < n_size; ++irow) {
            std::cout << "X[" << irow << "] = " << (*X_New)[irow] << "\n";
        }
        std::cout << "Number of Iterations: " << Iteration << "\n";
    }

    MPI_Finalize();
    return 0;
}
