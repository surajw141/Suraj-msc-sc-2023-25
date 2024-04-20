// Matrixops.cpp
#include "gaussh.hpp"

Matrixops::Matrixops() : mat(nullptr), rows(0), cols(0) {}

Matrixops::~Matrixops()
{
    if (mat != nullptr)
    {
        for (int r = 0; r < rows; r++)
            delete[] mat[r];
        delete[] mat;
    }
}

void Matrixops::readMatrix(const string &filename_l, const string &filename_r)
{
    ifstream fin;
    fin.open(filename_l);
    fin >> rows >> cols;

    mat = new double *[rows];
    for (int i = 0; i < rows; ++i)
        mat[i] = new double[cols];

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols - 1; ++c)
            fin >> mat[r][c];
    }
    fin.close();

    fin.open(filename_r);
    for (int i = 0; i < rows; i++)
        fin >> mat[i][cols - 1];
    fin.close();
}

void Matrixops::printMatrix()
{
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            cout << mat[r][c] << " ";
        }
        cout << endl;
    }
}

void Matrixops::uppertriangular()
{
    for (int r = 0; r < rows; r++)
    {
        double pivot = mat[r][r];
        for (int c = 0; c < cols; ++c)
            mat[r][c] = mat[r][c] / pivot;

        for (int k = r + 1; k < rows; k++)
        {
            double tmp = mat[k][r];
            for (int c = 0; c < cols; c++)
                mat[k][c] = mat[k][c] + (-tmp) * mat[r][c];
        }

        // printMatrix();
        cout << "\n +++++++++++++++++++++++++++++++\n ";
    }
}

void Matrixops::backSubstitution()
{
    float *ans = new float[cols - 2];
    ans[cols - 2] = mat[rows - 1][cols - 1];

    for (int r = rows - 2; r >= 0; --r)
    {
        float lhs = 0.0;
        for (int c = r + 1; c < cols - 1; ++c)
            lhs += mat[r][c] * ans[c];

        ans[r] = mat[r][cols - 1] - lhs;
    }

    cout << "\n Solution :: ";
    for (int i = 0; i < cols - 1; i++)
        cout << ans[i] << " \n";
    cout << endl;

    delete[] ans;
}
