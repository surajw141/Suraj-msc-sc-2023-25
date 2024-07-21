#include <bits/stdc++.h>
#include "LU.hpp"
using namespace std;

Matrix::Matrix()
{
    cout << "L U Decomposition " << endl;
}

Matrix::Matrix(int r, int c)
{
    this->Rows = r;
    this->Cols = c;
    this->Mat.resize(Rows, std::vector<double>(Cols, 0));
    init();
}
void Matrix::init()
{
    for (size_t i = 0; i < Rows; i++)
    {
        for (size_t j = 0; i < Cols; i++)
        {
            Mat[i][j] = 0;
        }
    }
}

void Matrix::ReadMatrixFromFile(string MatrixFile)
{
    ifstream Fin;
    Fin.open(MatrixFile);
    if (!Fin)
    {
        cout << "Error:Unable to open matrix file!" << endl;
        exit(1);
    }

    Fin >> Rows >> Cols;
    // this->Mat.resize(Rows, std::vector<double>(Cols, 0));

    cout << "\n No of rows::" << Rows << "\tNo of cols::" << Cols << endl;
    Mat = vector<vector<double>>(Rows, vector<double>(Cols));

    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Cols; j++)
        {
            Fin >> Mat[i][j];
        }
    }
    Fin.close();
}

void Matrix::PrintMatrix()
{
    for (int i = 0; i < Mat.size(); i++)
    {
        for (int j = 0; j < Mat[i].size(); j++)
        {
            cout << Mat[i][j] << " ";
        }
        cout << endl;
    }
}
double Matrix::GetUpperTriangular(Matrix L, Matrix U, int rowIndex, int colIndex)
{
    if (rowIndex == colIndex)
    {
        return 1;
    }
    double ans;
    ans = Mat[rowIndex][colIndex];
    double temp = 0;
    for (int k = 0; k < rowIndex; k++)
    {
        temp += L.Mat[rowIndex][k] * U.Mat[k][colIndex];
    }
    ans = (ans - temp) / L.Mat[rowIndex][rowIndex];
    return ans;
}
double Matrix::GetLowerTriangular(Matrix L, Matrix U, int rowIndex, int colIndex)
{
    double ans;
    ans = Mat[rowIndex][colIndex];
    double temp = 0.0;
    for (int k = 0; k < colIndex; k++)
    {
        temp += L.Mat[rowIndex][k] * U.Mat[k][colIndex];
    }
    ans = ans - temp;
    return ans;
}

void Matrix::LUDecomposition()
{

    Matrix L(this->Rows, this->Cols);
    Matrix U(this->Rows, this->Cols);

    // for (int i = 0; i < Rows; i++)
    //     U.Mat[i][i] = 1;

    for (int rowIndex = 0; rowIndex < Rows; rowIndex++)
    {
        for (int colIndex = 0; colIndex < Cols; colIndex++)

            if (colIndex >= rowIndex)
                L.Mat[colIndex][rowIndex] = GetLowerTriangular(L, U, colIndex, rowIndex);

        for (int colIndex = 0; colIndex < Cols; colIndex++)

            if (colIndex >= rowIndex)
                U.Mat[rowIndex][colIndex] = GetUpperTriangular(L, U, rowIndex, colIndex);
    }

    cout << "Get Lower tariangular matrix:" << endl;
    L.PrintMatrix();
    cout << "Get Upper triangular matrix:" << endl;
    U.PrintMatrix();
}