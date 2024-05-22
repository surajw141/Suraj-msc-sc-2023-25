#include "IterativeSolvers.hpp"
#include <cmath>
#include <iostream>

// Gauss-Jacobi Method
std::vector<double> IterativeSolvers::gaussJacobi(const std::vector<std::vector<double>> &A,
                                                  const std::vector<double> &b,
                                                  const std::vector<double> &initialGuess,
                                                  int maxIterations,
                                                  double tolerance)
{
    int n = A.size();
    std::vector<double> x = initialGuess;
    std::vector<double> xOld = initialGuess;

    for (int k = 0; k < maxIterations; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            double sum = b[i];

            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                {
                    sum -= A[i][j] * xOld[j];
                }
            }

            x[i] = sum / A[i][i];
        }

        double error = 0.0;
        for (int i = 0; i < n; ++i)
        {
            error += std::fabs(x[i] - xOld[i]);
        }

        if (error < tolerance)
        {
            break;
        }

        xOld = x;
    }

    return x;
}

// Gauss-Seidel Method
std::vector<double> IterativeSolvers::gaussSeidel(const std::vector<std::vector<double>> &A,
                                                  const std::vector<double> &b,
                                                  const std::vector<double> &initialGuess,
                                                  int maxIterations,
                                                  double tolerance)
{
    int n = A.size();
    std::vector<double> x = initialGuess;

    for (int k = 0; k < maxIterations; ++k)
    {
        std::vector<double> xOld = x;

        for (int i = 0; i < n; ++i)
        {
            double sum = b[i];

            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                {
                    sum -= A[i][j] * x[j];
                }
            }

            x[i] = sum / A[i][i];
        }

        double error = 0.0;
        for (int i = 0; i < n; ++i)
        {
            error += std::fabs(x[i] - xOld[i]);
        }

        if (error < tolerance)
        {
            break;
        }
    }

    return x;
}
