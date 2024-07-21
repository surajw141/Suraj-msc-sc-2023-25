#include "MatrixClass.hpp"

int main()
{
    Matrix mat;
    mat.readMatrixViaFiles("matrixL.txt", "matrixR.txt");
    mat.display();
    mat.guassSeidel();
    return 0;
}
