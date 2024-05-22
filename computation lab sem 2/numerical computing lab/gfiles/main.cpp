#include "MatrixClass.hpp"

int main()
{
    Matrix mat;
    string fileL = "leftMatrix.txt";
    string fileR = "rightMatrix.txt";

    mat.readMatrixViaFiles(fileL, fileR);
    mat.display();
    mat.guassSeidel();

    return 0;
}
