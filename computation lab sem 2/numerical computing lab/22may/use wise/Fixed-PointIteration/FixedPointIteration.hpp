#ifndef FIXEDPOINTITERATION_HPP
#define FIXEDPOINTITERATION_HPP

#include <functional>

class FixedPointIteration
{
public:
    // Fixed Point Iteration Method
    static double fixedPoint(std::function<double(double)> g,
                             double initialGuess,
                             int maxIterations,
                             double tolerance);
};

#endif // FIXEDPOINTITERATION_HPP
