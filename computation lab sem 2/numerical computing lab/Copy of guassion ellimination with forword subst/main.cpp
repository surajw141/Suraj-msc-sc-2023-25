#include "gaussh.hpp"

// main.cpp
int main()
{
    Matrixops ops;
    string filename_3 = "L_3.txt";
    string filename_31 = "R_3.txt";

    ops.readMatrix(filename_3, filename_31);
    ops.printMatrix();
    cout << "\n +++++++++++++++++++++++++++++++\n ";
    ops.lowertriangular();
    ops.forwardSubstitution();

    return 0;
}
