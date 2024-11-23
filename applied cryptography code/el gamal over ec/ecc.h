#ifndef ECC_H
#define ECC_H

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

struct Point
{
    ZZ x, y;
};

// Elliptic Curve parameters (you can change these as needed)
extern ZZ p; // Prime modulus
extern ZZ a; // Curve parameter a
extern ZZ b; // Curve parameter b

// Identity point at infinity
extern Point identity;

// Function declarations
bool isOnCurve(Point P);
Point addPoints(Point P, Point Q);
Point multiplyPoint(Point P, ZZ k);

#endif // ECC_H
