#ifndef ITERATIVESOLVERS_HPP
#define ITERATIVESOLVERS_HPP

#include <vector>

class IterativeSolvers
{
public:
    // Gauss-Jacobi Method
    static std::vector<double> gaussJacobi(const std::vector<std::vector<double>> &A,
                                           const std::vector<double> &b,
                                           const std::vector<double> &initialGuess,
                                           int maxIterations,
                                           double tolerance);

    // Gauss-Seidel Method
    static std::vector<double> gaussSeidel(const std::vector<std::vector<double>> &A,
                                           const std::vector<double> &b,
                                           const std::vector<double> &initialGuess,
                                           int maxIterations,
                                           double tolerance);
};

#endif // ITERATIVESOLVERS_HPP
