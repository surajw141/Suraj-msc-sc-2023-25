#include "LinearSystemSolvers.hpp"
#include <stdexcept>
#include <iostream>

// Gaussian Elimination Method
std::vector<double> LinearSystemSolvers::gaussianElimination(std::vector<std::vector<double>> A, std::vector<double> b)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            double factor = A[k][i] / A[i][i];
            for (int j = 0; j < n; j++)
            {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return x;
}

// LU Decomposition Method
void LinearSystemSolvers::luDecomposition(const std::vector<std::vector<double>> &A,
                                          std::vector<std::vector<double>> &L,
                                          std::vector<std::vector<double>> &U)
{
    int n = A.size();
    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int k = i; k < n; k++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
            {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - sum;
        }
        for (int k = i; k < n; k++)
        {
            if (i == k)
            {
                L[i][i] = 1;
            }
            else
            {
                double sum = 0.0;
                for (int j = 0; j < i; j++)
                {
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}
