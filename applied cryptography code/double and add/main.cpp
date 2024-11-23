// main.cpp
#include <iostream>
#include "DoubleAndAdd.hpp"

int main()
{
    Point P = {3, 6}; // Starting point on the curve
    long long k = 3;  // Scalar multiplier

    Point result = scalarMultiply(P, k);
    std::cout << "Result of " << k << " * (" << P.first << ", " << P.second << ") is: ("
              << result.first << ", " << result.second << ")\n";

    return 0;
}
