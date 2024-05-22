#include <iostream>
#include <vector>
#include <cmath>
#include "NumericalMethods.hpp"

int main()
{
    // Example usage of Gauss-Seidel Method
    std::vector<std::vector<double>> A1 = {
        {4, 1, 2},
        {3, 5, 1},
        {1, 1, 3}};

    std::vector<double> b1 = {4, 7, 3};
    std::vector<double> initialGuess1 = {0, 0, 0};
    int maxIterations = 100;
    double tolerance = 1e-6;

    std::vector<double> solution1 = NumericalMethods::gaussSeidel(A1, b1, initialGuess1, maxIterations, tolerance);
    std::cout << "Gauss-Seidel Solution:" << std::endl;
    for (double x : solution1)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Example usage of Gauss-Jacobi Method
    std::vector<double> solution2 = NumericalMethods::gaussJacobi(A1, b1, initialGuess1, maxIterations, tolerance);
    std::cout << "Gauss-Jacobi Solution:" << std::endl;
    for (double x : solution2)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Example usage of Fixed Point Iteration
    auto g = [](double x)
    { return std::cos(x); };
    double initialGuess2 = 0.5;
    double solution3 = NumericalMethods::fixedPoint(g, initialGuess2, maxIterations, tolerance);
    std::cout << "Fixed Point Iteration Solution:" << std::endl;
    std::cout << solution3 << std::endl;

    // Example usage of Cholesky Decomposition
    std::vector<std::vector<double>> A2 = {
        {4, 12, -16},
        {12, 37, -43},
        {-16, -43, 98}};

    try
    {
        std::vector<std::vector<double>> L = NumericalMethods::cholesky(A2);
        std::cout << "Cholesky Decomposition (L):" << std::endl;
        for (const auto &row : L)
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

    // Example usage of Bisection Method
    auto f = [](double x)
    { return x * x - 2; };
    double a = 0.0;
    double b = 2.0;
    double solution4 = NumericalMethods::bisection(f, a, b, maxIterations, tolerance);
    std::cout << "Bisection Method Solution:" << std::endl;
    std::cout << solution4 << std::endl;

    return 0;
}