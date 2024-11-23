#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>

using namespace std;
using namespace NTL;

// Define the Elliptic Curve parameters (over a finite field)
ZZ p = conv<ZZ>("23"); // Prime modulus for finite field F_p
ZZ a = conv<ZZ>("1");  // Elliptic curve parameter a
ZZ b = conv<ZZ>("1");  // Elliptic curve parameter b

// Elliptic curve equation: y^2 = x^3 + ax + b (mod p)

// Elliptic Curve point addition (mod p)
struct Point
{
    ZZ x, y;
};

// Check if a point is on the elliptic curve
bool isOnCurve(Point P)
{
    ZZ lhs = P.y * P.y;
    ZZ rhs = (P.x * P.x * P.x + a * P.x + b) % p;
    return lhs == rhs;
}

// Add two points P and Q on the elliptic curve (P + Q)
Point addPoints(Point P, Point Q)
{
    ZZ m, x3, y3;

    if (P.x == Q.x && P.y == Q.y)
    { // Point doubling
        m = (3 * P.x * P.x + a) * InvMod(2 * P.y, p) % p;
    }
    else
    { // Point addition
        m = (Q.y - P.y) * InvMod(Q.x - P.x, p) % p;
    }

    x3 = (m * m - P.x - Q.x) % p;
    y3 = (m * (P.x - x3) - P.y) % p;

    return {x3, y3};
}

// Multiply a point P by an integer k (Scalar multiplication)
Point multiplyPoint(Point P, ZZ k)
{
    Point result = {0, 0}; // Identity element (point at infinity)
    Point current = P;

    while (k > 0)
    {
        if (k % 2 == 1)
        {
            result = addPoints(result, current);
        }
        current = addPoints(current, current); // Double the point
        k /= 2;
    }
    return result;
}
