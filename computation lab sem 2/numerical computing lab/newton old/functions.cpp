// functions.cpp
#include <cmath>
#include "bisection.hpp"

double f(double x)
{
    return pow(x, 3) - 5 * x + 3;
}

double df(double x)
{
    return 3 * pow(x, 2) - 5;
}

double newton_raphson(double x0, double tol, int max_iter)
{
    double x = x0;
    int iter = 0;
    while (iter < max_iter)
    {
        double fx = f(x);
        double dfx = df(x);
        double u = fx / dfx;
        double rate_of_sharing = (dfx - df(x - u)) / dfx;
        x = x - rate_of_sharing * u;
        if (abs(u) < tol)
        {
            return x;
        }
        iter++;
    }
    return NAN; // Return NaN if method doesn't converge within max_iter iterations
}
///\\\\cpp