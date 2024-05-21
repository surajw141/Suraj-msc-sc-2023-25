#include "MatrixClass.hpp"

vector<Matrix> Matrix::lowerUpperDecomposition()
{
    // vector<Matrix> D(2);
    vector<Matrix> D;
    Matrix M1(this->rows, this->cols);
    Matrix M2(rows, cols);
    // To use operator overloading here
    double **U = M1.mat;
    double **L = M2.mat;
    // Approach -- Crout's Method
    for (int i = 0; i < rows; i++)
    {
        U[i][i] = 1;
    }

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            // Go first across the 1st col of L,then 2nd and so on...
            if (c >= r)
            {
                L[c][r] = computeL(mat, L, U, c, r);
            }
        }
        for (int c = 0; c < cols; c++)
        {
            // Go across 1st row of U,then 2nd and so on...
            if (c > r)
            {
                U[r][c] = computeU(mat, U, L, r, c);
            }
        }
    }
    // M1.display();
    // A deep copy is required..hence a copy constructor is a must!
    D.push_back(M1);
    D.push_back(M2);
    // D.emplace_back(M1);
    return D;
}

double Matrix::computeL(double **mat, double **L, double **U, int row, int col)
{
    double ans, sum = 0.0;
    ans = mat[row][col];
    for (int k = 0; k < col; k++)
    {
        sum += L[row][k] * U[k][col];
    }
    ans -= sum;
    return ans;
}

double Matrix::computeU(double **mat, double **U, double **L, int row, int col)
{
    double ans, sum = 0.0;
    ans = mat[row][col];
    for (int k = 0; k < row; k++)
    {
        sum += L[row][k] * U[k][col];
    }
    ans -= sum;
    return ans / L[row][row];
}