#include <bits/stdc++.h>
#include "LU.hpp"
using namespace std;

int main()
{
    Matrix matrix;

    string MatrixFile = "input.txt";
    matrix.ReadMatrixFromFile(MatrixFile);
    matrix.PrintMatrix();
    matrix.LUDecomposition();
    
    return 0;
}