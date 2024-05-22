#include "FixedPointIteration.hpp"
#include <cmath>

// Fixed Point Iteration Method
double FixedPointIteration::fixedPoint(std::function<double(double)> g,
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
