#include <bits/stdc++.h>
using namespace std;
//
void printMatrix(double **mat, int rows, int cols)
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

int main()

{
    // string filename_3 = "L_3.txt";
    // string filename_31 = "R_3.txt";

    string filename_L49 = "files/L_49_49.txt";
    string filename_R49 = "files/R_49.txt";

    // string filename_225 = "L_225_225.txt";ṇ
    // string filename_100 = "R_225.txt";

    string filename_l = filename_L49;
    string filename_r = filename_R49;

    ifstream fin;
    fin.open(filename_l);
    int rows, cols;
    fin >> rows >> cols;
    cout << "\n rows :: " << rows << "\t cols :: " << cols << endl;

    double **mat = new double *[rows];
    for (int i = 0; i < rows; ++i)
    {
        mat[i] = new double[cols];
    }

    // read the matrix
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols - 1; ++c)
        {
            fin >> mat[r][c];
        }
    }
    fin.close();
    fin.open(filename_r);
    for (int i = 0; i < rows; i++)
        fin >> mat[i][cols - 1];

    fin.close();

    printMatrix(mat, rows, cols);
    cout << "\n +++++++++++++++++++++++++++++++\n ";

    // Gaussian elimination
    // 1. Reduce to upper triangular matrix
    //  1.1 divide each row by pivot element
    for (int r = 0; r < rows; r++)
    {
        double pivot = mat[r][r];
        for (int c = 0; c < cols; ++c)
            mat[r][c] = mat[r][c] / pivot;

        // 1.2 reduce elements below the element
        for (int k = r + 1; k < rows; k++)
        {
            double tmp = mat[k][r];
            for (int c = 0; c < cols; c++)
            {
                // R2 + (-3)R1
                mat[k][c] = mat[k][c] + (-tmp) * mat[r][c];
            }
        }

        printMatrix(mat, rows, cols);
        cout << "\n +++++++++++++++++++++++++++++++\n ";
    }

    // 1.2 subtract each row from the row above it

    // 2. Back substitution
    float *ans = new float[cols - 2];
    ans[cols - 2] = mat[rows - 1][cols - 1];

    for (int r = rows - 2; r >= 0; --r)
    {
        float lhs = 0.0;
        for (int c = r + 1; c < cols - 1; ++c)
        {
            lhs += mat[r][c] * ans[c];
        }
        // cout << "\n lhs :: " << lhs << "\t r :: " << r << endl;

        // 2. update ans
        ans[r] = mat[r][cols - 1] - lhs;
    }

    cout << "\n Solution :: ";
    for (int i = 0; i < cols - 1; i++)
        cout << ans[i] << " \n";
    cout << endl;

    // clean up
    delete[] ans;
    for (int r = 0; r < rows; r++)
    {
        delete[] mat[r];
    }
    delete[] mat;

    // 3. Print result

    return 0;
}

// gnuplot > plot "file.txt" w lp

// R S agrawal - book
// numerical algorithm implementation - git hub
// what idea, domain, my responsibilities, technologies, github link