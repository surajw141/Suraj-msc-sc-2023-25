#include "NumericalMethods.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Gauss-Seidel Method
std::vector<double> NumericalMethods::gaussSeidel(const std::vector<std::vector<double>> &A,
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

// Gauss-Jacobi Method
std::vector<double> NumericalMethods::gaussJacobi(const std::vector<std::vector<double>> &A,
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

// Fixed Point Iteration
double NumericalMethods::fixedPoint(std::function<double(double)> g,
                                    double initialGuess,
                                    int maxIterations,
                                    double tolerance)
{
    double x = initialGuess;

    for (int k = 0; k < maxIterations; ++k)
    {
        double xNew = g(x);

        if (std::fabs(xNew - x) < tolerance)
        {
            return xNew;
        }

        x = xNew;
    }

    return x;
}

// Cholesky Decomposition
std::vector<std::vector<double>> NumericalMethods::cholesky(const std::vector<std::vector<double>> &A)
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

// Bisection Method
double NumericalMethods::bisection(std::function<double(double)> f,
                                   double a,
                                   double b,
                                   int maxIterations,
                                   double tolerance)
{
    if (f(a) * f(b) >= 0)
    {
        throw std::invalid_argument("The function must have different signs at the endpoints.");
    }

    double mid = a;
    for (int k = 0; k < maxIterations; ++k)
    {
        mid = (a + b) / 2.0;
        double fMid = f(mid);

        if (std::fabs(fMid) < tolerance)
        {
            return mid;
        }

        if (f(a) * fMid < 0)
        {
            b = mid;
        }
        else
        {
            a = mid;
        }
    }

    return mid;
}
