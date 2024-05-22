#include <bits/stdc++.h>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    double **mat;

public:
    Matrix();
    Matrix(int r, int c);
    ~Matrix();
    void Readfiles();
    int getDDRowAt(int r);
    void gaussJacobi(vector<double> &initialGuess, double tol, int maxIter);
};

// Default constructor
Matrix::Matrix() : rows(0), cols(0), mat(nullptr) {}

// Parameterized constructor
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    mat = new double *[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new double[cols];
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

// Function to read files and fill matrix
void Matrix::Readfiles() {
    ifstream fin("input.txt");

    fin >> rows >> cols;

    // Deallocate previous memory if already allocated
    if (mat) {
        for (int i = 0; i < rows; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }

    // Allocate new memory
    mat = new double *[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new double[cols];
    }

    // Read the matrix from the first file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fin >> mat[i][j];
        }
    }
    fin.close();

    // Open the second file
    fin.open("temp.txt");

    // Read the matrix from the second file
    for (int i = 0; i < rows; i++) {
        fin >> mat[i][cols - 1];
    }
    fin.close();
}

// Function to get diagonally dominant row at r
int Matrix::getDDRowAt(int r) {
    for (int i = r + 1; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols - 1; j++) {
            if (r != j) {  // Use j instead of c (likely typo in your original code)
                sum += fabs(mat[i][j]);
            }
        }
        if (fabs(mat[i][r]) >= sum) {
            return i;
        }
    }
    cout << "No diagonally dominant row found starting from row " << r << endl;
    return -1;
}

// Function to perform Gauss-Jacobi iteration
void Matrix::gaussJacobi(vector<double> &initialGuess, double tol, int maxIter) {
    vector<double> xNew(rows, 0.0);
    vector<double> xOld = initialGuess;
    int iter = 0;

    while (iter < maxIter) {
        for (int i = 0; i < rows; ++i) {
            double sum = mat[i][cols - 1];
            for (int j = 0; j < cols - 1; ++j) {
                if (i != j) {
                    sum -= mat[i][j] * xOld[j];
                }
            }
            xNew[i] = sum / mat[i][i];
        }

        bool convergence = true;
        for (int i = 0; i < rows; ++i) {
            if (fabs(xNew[i] - xOld[i]) > tol) {
                convergence = false;
                break;
            }
        }

        if (convergence) {
            break;
        }

        xOld = xNew;
        ++iter;
    }

    cout << "Solution after " << iter << " iterations:" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << xNew[i] << " ";
    }
    cout << endl;
}

int main() {
    Matrix matrix;
    matrix.Readfiles();

    vector<double> initialGuess(matrix.getRows(), 0.0);  // Example initial guess
    double tol = 1e-6;
    int maxIter = 100;

    matrix.gaussJacobi(initialGuess, tol, maxIter);

    return 0;
}
