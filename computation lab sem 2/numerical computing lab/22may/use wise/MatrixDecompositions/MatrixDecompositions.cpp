#include "MatrixDecompositions.hpp"
#include <cmath>
#include <stdexcept>

// Cholesky Decomposition Method
std::vector<std::vector<double>> MatrixDecompositions::cholesky(const std::vector<std::vector<double>> &A)
{
    int n = A.size();
    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            double sum = 0.0;

            for (int k = 0; k < j; ++k)
            {
                sum += L[i][k] * L[j][k];
            }

            if (i == j)
            {
                if (A[i][i] - sum <= 0.0)
                {
                    throw std::runtime_error("Matrix is not positive definite.");
                }
                L[i][j] = std::sqrt(A[i][i] - sum);
            }
            else
            {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    return L;
}
