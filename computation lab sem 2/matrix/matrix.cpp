#include <matrix.hpp>
class matrix
{
    double **mat;
    int rows, cols;
};

bool isDigonallyDominant(Matrix &mat)
{
    for (int i = 0; i < mat.rows; i++)
    {
        double sum = 0;
        for (int j = 0; j < mat.cols; j++)
        {
            if (i != j)
                sum += abs(mat.mat[i * mat.cols + j]);
        }
        if (abs(mat.mat[i * mat.cols + i]) <= sum)
            return false;
    }
    return true;
}