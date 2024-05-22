#include "jacobi.hpp"

int main() {
    Matrix matrix;
    matrix.Readfiles();

    std::vector<double> initialGuess(matrix.getRows(), 0.0);  // Example initial guess
    double tol = 1e-6;
    int maxIter = 100;

    matrix.gaussJacobi(initialGuess, tol, maxIter);

    return 0;
}
