#ifndef NUMERICALMETHODS_HPP
#define NUMERICALMETHODS_HPP

#include <vector>
#include <functional>

class NumericalMethods
{
public:
    // Gauss-Seidel Method
    static std::vector<double> gaussSeidel(const std::vector<std::vector<double>> &A,
                                           const std::vector<double> &b,
                                           const std::vector<double> &initialGuess,
                                           int maxIterations,
                                           double tolerance);

    // Gauss-Jacobi Method
    static std::vector<double> gaussJacobi(const std::vector<std::vector<double>> &A,
                                           const std::vector<double> &b,
                                           const std::vector<double> &initialGuess,
                                           int maxIterations,
                                           double tolerance);

    // Fixed Point Iteration
    static double fixedPoint(std::function<double(double)> g,
                             double initialGuess,
                             int maxIterations,
                             double tolerance);

    // Cholesky Decomposition
    static std::vector<std::vector<double>> cholesky(const std::vector<std::vector<double>> &A);

    // Bisection Method
    static double bisection(std::function<double(double)> f,
                            double a,
                            double b,
                            int maxIterations,
                            double tolerance);
};

#endif // NUMERICALMETHODS_HPP
