
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#include "MatrixClass.hpp"
// #include "guassianElimination.cpp"

// The default constructor does only shallow copy.
Matrix::Matrix()
{
    mat = NULL;
    rows = cols = 0;
    // cout<<"\n dc -> created object @ :: "<<this<<endl;
}

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    // Dynamic Memory Allocation of 2d matrix;
    mat = new double *[rows]; // array of pointers
    for (int t = 0; t < rows; t++)
    {
        mat[t] = new double[cols]; // each pointer pointing to a mem. block of size 'cols'
    }
    // Initialize with zeroes
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = 0;
        }
    }
    // cout<<"\n pc => created object @ :: "<<this<<endl;
}

Matrix::Matrix(const Matrix &T)
{
    // cout<<"\n copyc => created object @ :: "<<this<<endl;
    rows = T.rows;
    cols = T.cols;
    mat = new double *[rows];
    for (int t = 0; t < rows; t++)
    {
        mat[t] = new double[cols]; // each pointer pointing to a mem. block of size 'cols'
    }
    // deep copy is copying the memory values, not the pointer
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = T.mat[i][j];
        }
    }
}

void Matrix::display()
{
    // int r = this->rows, c = this->cols;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "\n";
}

void Matrix::readMatrixFromUser()
{
    cout << "Enter the number of rows and cols : ";
    cin >> rows >> cols;

    // Dynamic Memory Allocation of 2d matrix;
    mat = new double *[rows]; // array of pointers
    for (int t = 0; t < rows; t++)
    {
        mat[t] = new double[cols];
    }

    cout << "Enter the elements of the matrix one after another" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (cols); j++)
        {
            cin >> mat[i][j];
        }
    }
}

bool Matrix::isDiagonallyDominant()
{
    // |a_ii| >= Summation from j = 1 to n of |a_ij| s.t i != j
    if (mat != NULL)
    {
        for (int r = 0; r < rows; r++)
        {
            double sum = 0.0;
            for (int c = 0; c < cols - 1; (c == r - 1) ? c += 2 : c++)
            {
                if (r == c && c == 0)
                    continue;
                sum += fabs(mat[r][c]);
            }
            if (fabs(mat[r][r]) <= sum)
                return false;
            sum = 0.0;
        }
        return true;
    }
    return false;
}

bool Matrix::makeDiagonallyDominant()
{
    for (int r = 0; r < rows; r++)
    {
        // find a non DD row
        double s = 0.0;
        for (int c = 0; c < cols - 1; c++)
        {
            if (r != c)
                s += fabs(mat[r][c]);
        }
        if (s > fabs(mat[r][r]))
        {
            int index = getDDRow(r);
            if (index != -1)
                swapRows(r, index);
            else
                return false;
        }
    }
    return true;
}

int Matrix::getDDRow(int row)
{
    for (int i = row + 1; i < rows; i++)
    {
        double s = 0.0;
        for (int j = 0; j < cols - 1; j++)
        {
            // check for DD Row corresponding to {row}(th) column
            if (row != j)
                s += fabs(mat[i][j]);
        }
        if (fabs(mat[i][row]) >= s)
            return i;
    }
    cout << "No Diagonally Domininant row found after Row " << row << endl;
    return -1;
}

void Matrix::swapRows(int r1, int r2)
{
    for (int i = 0; i < cols; i++)
    {
        swap(mat[r1][i], mat[r2][i]);
    }
}

void Matrix::readMatrixViaFiles(string fileL, string fileR)
{
    ifstream fin;
    fin.open(fileL);
    fin >> rows >> cols;
    // cout << "Rows :: " << rows << "\nCols :: " << cols << endl;

    // Dynamic Memory Allocation of 2d matrix;
    mat = new double *[rows];
    for (int t = 0; t < rows; t++)
    {
        mat[t] = new double[cols];
    }

    // Read Left Matrix File
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (cols - 1); j++)
        {
            fin >> mat[i][j];
        }
    }

    fin.close();
    fin.open(fileR);

    // Read in Right Matrix
    for (int i = 0; i < rows; i++)
    {
        fin >> mat[i][cols - 1];
    }
    fin.close();
    display();
}

// pass answer array as reference
//  void Matrix::backSubstitution(double** M, double (&ans)[]){
//  template<class T, std::size_t S>
void Matrix::backSubstitution(double **M, double *ans)
{
    double lhs = 0.0;
    ans[cols - 2] = M[rows - 1][cols - 1];
    for (int r = rows - 2; r >= 0; r--)
    { // starting from 2nd last row
        for (int c = r + 1; c < cols - 1; c++)
        { // starting from the element just after pivot position
            lhs += M[r][c] * ans[c];
        }
        ans[r] = (M[r][cols - 1] - lhs) / M[r][r];
        lhs = 0;
    }
    // return ans;
}

void Matrix::forwardSubstitution(double **M, double *ans)
{
    double lhs;
    ans[0] = M[0][cols - 1] / M[0][0];
    for (int r = 1; r < rows; r++)
    { // starting from second row
        for (int c = 0; c < r; c++)
        { // starting from the element just after pivot position
            lhs += M[r][c] * ans[c];
        }
        ans[r] = (M[r][cols - 1] - lhs) / M[r][r];
        lhs = 0;
    }

    // for (int i = 0; i < cols-1; i++){
    //         // print the values
    //         cout << ans[i] << endl;
    // }
}

bool Matrix::isSymmetric()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            if (i > j)
            {
                if (mat[i][j] != mat[j][i])
                    return false;
            }
        }
    }
    return true;
}

vector<vector<double>> Matrix::transpose()
{
    vector<vector<double>> M(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (cols); j++)
        {
            // since we are dealing with transpose of a "lower" triangular matrix
            if (i >= j)
                M[j][i] = mat[i][j];
            else
                M[i][j] = 0;
        }
    }
    return M;
}

Matrix::~Matrix()
{
    // free allocated memory
    //  cout << "Calling Destructor for Object @"<< this <<endl;
    if (mat != NULL)
    {
        for (int j = 0; j < rows; j++)
        {
            delete[] mat[j];
        }
        delete[] mat;
    }
}
