#include "RootFindingMethods.hpp"
#include <stdexcept>
#include <cmath>

// Bisection Method
double RootFindingMethods::bisection(std::function<double(double)> f,
                                     double a,
                                     double b,
                                     int maxIterations,
                                     double tolerance)
{
    if (f(a) * f(b) >= 0)
    {
        throw std::invalid_argument("The function must have different signs at the endpoints.");
    }

    double mid = a;
    for (int k = 0; k < maxIterations; ++k)
    {
        mid = (a + b) / 2.0;
        double fMid = f(mid);

        if (std::fabs(fMid) < tolerance)
        {
            return mid;
        }

        if (f(a) * fMid < 0)
        {
            b = mid;
        }
        else
        {
            a = mid;
        }
    }

    return mid;
}

// Newton-Raphson Method
double RootFindingMethods::newtonRaphson(std::function<double(double)> f,
                                         std::function<double(double)> df,
                                         double initialGuess,
                                         int maxIterations,
                                         double tolerance)
{
    double x = initialGuess;

    for (int k = 0; k < maxIterations; ++k)
    {
        double fx = f(x);
        double dfx = df(x);

        if (std::fabs(dfx) < tolerance)
        {
            throw std::runtime_error("Derivative is too small.");
        }

        double xNew = x - fx / dfx;

        if (std::fabs(xNew - x) < tolerance)
        {
            return xNew;
        }

        x = xNew;
    }

    return x;
}
