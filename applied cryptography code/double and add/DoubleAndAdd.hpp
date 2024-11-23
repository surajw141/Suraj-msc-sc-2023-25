// DoubleAndAdd.hpp
#ifndef DOUBLE_AND_ADD_HPP
#define DOUBLE_AND_ADD_HPP

#include <utility>

// Define a point on the elliptic curve as a pair of integers
typedef std::pair<long long, long long> Point;

// Parameters of the elliptic curve
const long long a = 2;  // Coefficient 'a' in the curve equation y^2 = x^3 + ax + b
const long long b = 3;  // Coefficient 'b' in the curve equation
const long long p = 97; // Prime field, e.g., p = 97

// Function declarations
long long mod(long long x, long long p);
long long modInverse(long long x, long long p);
Point pointAdd(const Point &P, const Point &Q);
Point scalarMultiply(Point P, long long k);

#endif
