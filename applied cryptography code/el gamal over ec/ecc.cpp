#include "ecc.h"

// Define the Elliptic Curve parameters (over a finite field)
ZZ p = conv<ZZ>("23"); // Example prime modulus
ZZ a = conv<ZZ>("1");  // Example parameter a
ZZ b = conv<ZZ>("1");  // Example parameter b

// Identity point at infinity
Point identity = {conv<ZZ>("0"), conv<ZZ>("0")};

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
    if (P.x == identity.x && P.y == identity.y)
        return Q;
    if (Q.x == identity.x && Q.y == identity.y)
        return P;

    ZZ m, x3, y3;

    if (P.x == Q.x && P.y == Q.y)
    { // Point doubling
        if (P.y == 0)
            return identity; // Handle the case for point doubling of the point at infinity
        m = (3 * P.x * P.x + a) * InvMod(2 * P.y, p) % p;
    }
    else
    { // Point addition
        if (P.x == Q.x)
            return identity; // Handle point addition when points are vertical
        m = (Q.y - P.y) * InvMod(Q.x - P.x, p) % p;
    }

    x3 = (m * m - P.x - Q.x) % p;
    y3 = (m * (P.x - x3) - P.y) % p;

    return {x3, y3};
}

// Multiply a point P by an integer k (Scalar multiplication)
Point multiplyPoint(Point P, ZZ k)
{
    Point result = identity; // Identity element (point at infinity)
    Point current = P;

    while (k > 0)
    {
        if (k % 2 == 1)
        {
            result = addPoints(result, current);
        }
        current = addPoints(current, current); // Point doubling
        k /= 2;
    }
    return result;
}
