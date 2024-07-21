#ifndef ROOTFINDINGMETHODS_HPP
#define ROOTFINDINGMETHODS_HPP

#include <functional>

class RootFindingMethods
{
public:
    // Bisection Method
    static double bisection(std::function<double(double)> f,
                            double a,
                            double b,
                            int maxIterations,
                            double tolerance);

    // Newton-Raphson Method
    static double newtonRaphson(std::function<double(double)> f,
                                std::function<double(double)> df,
                                double initialGuess,
                                int maxIterations,
                                double tolerance);
};

#endif // ROOTFINDINGMETHODS_HPP
