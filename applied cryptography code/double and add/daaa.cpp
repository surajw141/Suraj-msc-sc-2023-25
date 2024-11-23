#include <iostream>
#include <utility> // For std::pair

// Define a point on the elliptic curve as a pair of integers
typedef std::pair<long long, long long> Point;

// Parameters of the elliptic curve
const long long a = 2;  // Coefficient 'a' in the curve equation y^2 = x^3 + ax + b
const long long b = 3;  // Coefficient 'b' in the curve equation
const long long p = 97; // Prime field, e.g., p = 97

// Modulo operation to handle negative values correctly
long long mod(long long x, long long p)
{
    return (x % p + p) % p;
}

// Extended Euclidean Algorithm to find modular inverse
long long modInverse(long long x, long long p)
{
    long long m0 = p, t, q;
    long long y = 0, z = 1;

    if (p == 1)
        return 0;

    while (x > 1)
    {
        q = x / p;
        t = p;
        p = x % p;
        x = t;
        t = y;
        y = z - q * y;
        z = t;
    }
    if (z < 0)
        z += m0;
    return z;
}

// Point addition on the elliptic curve
Point pointAdd(const Point &P, const Point &Q)
{
    if (P == std::make_pair(0LL, 0LL))
        return Q; // Identity point
    if (Q == std::make_pair(0LL, 0LL))
        return P; // Identity point
    if (P == Q)
    {
        // Point doubling
        long long s = mod((3 * P.first * P.first + a) * modInverse(2 * P.second, p), p);
        long long x_r = mod(s * s - 2 * P.first, p);
        long long y_r = mod(s * (P.first - x_r) - P.second, p);
        return {x_r, y_r};
    }
    else
    {
        // General point addition
        long long s = mod((Q.second - P.second) * modInverse(Q.first - P.first, p), p);
        long long x_r = mod(s * s - P.first - Q.first, p);
        long long y_r = mod(s * (P.first - x_r) - P.second, p);
        return {x_r, y_r};
    }
}

// Scalar multiplication using the Double-and-Add algorithm
Point scalarMultiply(Point P, long long k)
{
    Point Q = {0, 0}; // Initialize Q to the identity element (point at infinity)
    while (k > 0)
    {
        if (k & 1)
        {
            Q = pointAdd(Q, P); // Add P to Q if the current bit of k is 1
        }
        P = pointAdd(P, P); // Double the point P
        k >>= 1;            // Shift k right by 1 bit
    }
    return Q;
}

int main()
{
    Point P = {3, 6}; // Starting point on the curve
    long long k = 7;  // Scalar multiplier

    Point result = scalarMultiply(P, k);
    std::cout << "Result of " << k << " * (" << P.first << ", " << P.second << ") is: ("
              << result.first << ", " << result.second << ")\n";

    return 0;
}
