#include "gaussh.hpp"

int main()
{
    Matrixops ops;
    string filename_3 = "files/L_49_49.txt";
    string filename_31 = "files/R_49.txt";

    ops.readMatrix(filename_3, filename_31);
    ops.printMatrix();
    cout << "\n +++++++++++++++++++++++++++++++\n ";
    ops.uppertriangular();
    ops.backSubstitution();

    return 0;
}
