#ifndef DLP_H
#define DLP_H

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

using namespace NTL;

class DLP
{
public:
    DLP(ZZ p, ZZ_p g, int x); // Constructor
    ZZ bruteforce(ZZ_p h);    // Brute-force DLP function

private:
    ZZ_p g; // Generator
    int x;  // Upper bound for exponent search
};

#endif // DLP_H
