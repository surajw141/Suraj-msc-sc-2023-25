#include "MatrixClass.hpp"

Matrix::Matrix()
{
    mat = NULL;
    rows = cols = 0;
}

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols];
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    mat = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new double[cols];
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = other.mat[i][j];
        }
    }
}

Matrix::~Matrix()
{
    if (mat != NULL)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
    }
}

void Matrix::display()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

void Matrix::readMatrixViaFiles(string fileL, string fileR)
{
    ifstream fin;
    fin.open(fileL);
    if (!fin)
    {
        cerr << "Error opening file " << fileL << endl;
        exit(1);
    }
    fin >> rows >> cols;
    cout << "Matrix dimensions: " << rows << "x" << cols << endl;

    if (rows <= 0 || cols <= 0)
    {
        cerr << "Invalid matrix dimensions." << endl;
        exit(1);
    }

    // Rest of the code...
}

mat = new double *[rows];
for (int i = 0; i < rows; i++)
{
    mat[i] = new double[cols];
}

for (int i = 0; i < rows; i++)
{
    for (int j = 0; j < cols - 1; j++)
    {
        fin >> mat[i][j];
    }
}

fin.close();
fin.open(fileR);
if (!fin)
{
    cerr << "Error opening file " << fileR << endl;
    exit(1);
}

for (int i = 0; i < rows; i++)
{
    fin >> mat[i][cols - 1];
}
fin.close();
}

bool Matrix::isDiagonallyDominant()
{
    for (int r = 0; r < rows; r++)
    {
        double sum = 0.0;
        for (int c = 0; c < cols - 1; c++)
        {
            if (r != c)
            {
                sum += fabs(mat[r][c]);
            }
        }
        if (fabs(mat[r][r]) <= sum)
        {
            return false;
        }
    }
    return true;
}

bool Matrix::makeDiagonallyDominant()
{
    for (int r = 0; r < rows; r++)
    {
        double s = 0.0;
        for (int c = 0; c < cols - 1; c++)
        {
            if (r != c)
            {
                s += fabs(mat[r][c]);
            }
        }
        if (s > fabs(mat[r][r]))
        {
            int index = getDDRow(r);
            if (index != -1)
            {
                swapRows(r, index);
            }
            else
            {
                return false;
            }
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
            if (row != j)
            {
                s += fabs(mat[i][j]);
            }
        }
        if (fabs(mat[i][row]) >= s)
        {
            return i;
        }
    }
    return -1;
}

void Matrix::swapRows(int r1, int r2)
{
    for (int i = 0; i < cols; i++)
    {
        swap(mat[r1][i], mat[r2][i]);
    }
}

void Matrix::guassSeidel()
{
    if (!isDiagonallyDominant())
    {
        if (!makeDiagonallyDominant())
        {
            cout << "Matrix cannot be made diagonally dominant." << endl;
            return;
        }
    }

    bool flag = true;
    int count = 0;
    vector<double> var(rows, 0.0);
    vector<double> prev(rows, 0.0);

    while (flag)
    {
        prev = var;

        for (int r = 0; r < rows; r++)
        {
            double sum = 0.0;
            for (int c = 0; c < cols - 1; c++)
            {
                if (r != c)
                {
                    sum += mat[r][c] * var[c];
                }
            }
            var[r] = (mat[r][cols - 1] - sum) / mat[r][r];
        }

        double maxError = 0.0;
        for (int i = 0; i < rows; i++)
        {
            maxError = max(maxError, fabs(var[i] - prev[i]));
        }

        if (maxError <= TOLERANCE)
        {
            flag = false;
        }
        count++;
    }

    cout << "Iterations for Seidel ::" << count << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << var[i] << endl;
    }
}
