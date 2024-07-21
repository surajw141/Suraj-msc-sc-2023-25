#include "gaussh.hpp"

int main()
{
    Matrixops ops;
    string filename_3 = "files/7L_3.txt";
    string filename_31 = "files/7R_3 .txt";

    ops.readMatrix(filename_3, filename_31);
    ops.printMatrix();
    cout << "\n +++++++++++++++++++++++++++++++\n ";
    ops.uppertriangular();
    ops.backSubstitution();
    ops.forwardSubstitution();

    return 0;
}
