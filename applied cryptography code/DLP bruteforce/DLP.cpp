#include "DLP.h"
#include <iostream>

using namespace std;

// Constructor to initialize the generator g and upper bound x
DLP::DLP(ZZ p, ZZ_p generator, int upperBound)
{
    ZZ_p::init(p); // Initialize the modulus for ZZ_p field
    g = generator;
    x = upperBound;
}

// Brute-force method to solve the discrete logarithm problem
ZZ DLP::bruteforce(ZZ_p h)
{
    ZZ_p temp;
    for (int i = 1; i <= x; i++)
    {
        power(temp, g, i);
        if (temp == h)
        {
            return ZZ(i); // Return the integer value as a ZZ object
        }
    }
    return ZZ(-1); // Return -1 as a ZZ object to indicate failure
}
