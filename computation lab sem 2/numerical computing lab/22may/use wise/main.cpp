#include <iostream>
#include <vector>
#include <cmath>
#include "LinearSystemSolvers/LinearSystemSolvers.hpp"
#include "MatrixDecompositions/MatrixDecompositions.hpp"
#include "IterativeMethodsforSolvingLinearSystems/IterativeSolvers.hpp"
#include "Root-FindingMethods/RootFindingMethods.hpp"
#include "Fixed-PointIteration/FixedPointIteration.hpp"

int main()
{
    // Example usage of Gaussian Elimination
    std::vector<std::vector<double>> A1 = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}};
    std::vector<double> b1 = {8, -11, -3};
    std::vector<double> solution1 = LinearSystemSolvers::gaussianElimination(A1, b1);
    std::cout << "Gaussian Elimination Solution:" << std::endl;
    for (double x : solution1)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Example usage of LU Decomposition
    std::vector<std::vector<double>> L, U;
    LinearSystemSolvers::luDecomposition(A1, L, U);
    std::cout << "LU Decomposition (L):" << std::endl;
    for (const auto &row : L)
    {
        for (double val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "LU Decomposition (U):" << std::endl;
    for (const auto &row : U)
    {
        for (double val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Example usage of Cholesky Decomposition
    std::vector<std::vector<double>> A2 = {
        {4, 12, -16},
        {12, 37, -43},
        {-16, -43, 98}};
    try
    {
        std::vector<std::vector<double>> L2 = MatrixDecompositions::cholesky(A2);
        std::cout << "Cholesky Decomposition (L):" << std::endl;
        for (const auto &row : L2)
        {
            for (double val : row)
            {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Example usage of Gauss-Jacobi Method
    std::vector<double> initialGuess1 = {0, 0, 0};
    int maxIterations = 100;
    double tolerance = 1e-6;
    std::vector<double> solution2 = IterativeSolvers::gaussJacobi(A1, b1, initialGuess1, maxIterations, tolerance);
    std::cout << "Gauss-Jacobi Solution:" << std::endl;
    for (double x : solution2)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Example usage of Gauss-Seidel Method
    std::vector<double> solution3 = IterativeSolvers::gaussSeidel(A1, b1, initialGuess1, maxIterations, tolerance);
    std::cout << "Gauss-Seidel Solution:" << std::endl;
    for (double x : solution3)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Example usage of Bisection Method
    auto f = [](double x)
    { return x * x - 2; };
    double a = 0.0;
    double b = 2.0;
    double root1 = RootFindingMethods::bisection(f, a, b, maxIterations, tolerance);
    std::cout << "Bisection Method Root:" << std::endl;
    std::cout << root1 << std::endl;

    // Example usage of Newton-Raphson Method
    auto df = [](double x)
    { return 2 * x; };
    double initialGuess2 = 1.0;
    double root2 = RootFindingMethods::newtonRaphson(f, df, initialGuess2, maxIterations, tolerance);
    std::cout << "Newton-Raphson Method Root:" << std::endl;
    std::cout << root2 << std::endl;

    // Example usage of Fixed Point Iteration
    auto g = [](double x)
    { return std::cos(x); };
    double initialGuess3 = 0.5;
    double root3 = FixedPointIteration::fixedPoint(g, initialGuess3, maxIterations, tolerance);
    std::cout << "Fixed Point Iteration Root:" << std::endl;
    std::cout << root3 << std::endl;

    return 0;
}
