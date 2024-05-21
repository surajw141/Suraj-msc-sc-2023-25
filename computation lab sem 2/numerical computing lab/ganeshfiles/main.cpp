#include "MatrixClass.hpp"

int main()
{
    // Create a matrix object
    Matrix mat;

    // Read matrix from user
    mat.readMatrixFromUser();

    // Perform Gauss-Seidel method
    mat.guassSeidel();

    return 0;
}
