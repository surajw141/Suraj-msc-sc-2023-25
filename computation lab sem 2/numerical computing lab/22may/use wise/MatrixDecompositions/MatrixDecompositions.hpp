#ifndef MATRIXDECOMPOSITIONS_HPP
#define MATRIXDECOMPOSITIONS_HPP

#include <vector>

class MatrixDecompositions
{
public:
    // Cholesky Decomposition Method
    static std::vector<std::vector<double>> cholesky(const std::vector<std::vector<double>> &A);
};

#endif // MATRIXDECOMPOSITIONS_HPP
