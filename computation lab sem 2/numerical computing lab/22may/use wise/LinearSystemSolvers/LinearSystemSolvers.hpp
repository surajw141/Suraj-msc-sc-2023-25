#ifndef LINEARSYSTEMSOLVERS_HPP
#define LINEARSYSTEMSOLVERS_HPP

#include <vector>

class LinearSystemSolvers
{
public:
    // Gaussian Elimination Method
    static std::vector<double> gaussianElimination(std::vector<std::vector<double>> A, std::vector<double> b);

    // LU Decomposition Method
    static void luDecomposition(const std::vector<std::vector<double>> &A,
                                std::vector<std::vector<double>> &L,
                                std::vector<std::vector<double>> &U);
};

#endif // LINEARSYSTEMSOLVERS_HPP
