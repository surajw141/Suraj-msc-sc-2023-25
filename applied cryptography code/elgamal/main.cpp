#include "elgamal.h"
#include <NTL/ZZ.h>
#include <iostream>

using namespace std;
using namespace NTL;

int main()
{
    ZZ a, b, c;
    a = conv<ZZ>(12345); // Example values
    b = conv<ZZ>(678);
    c = conv<ZZ>(98765);

    ElGamal elgamal;
    ZZ x = elgamal.power(a, b, c); // Call the ElGamal class's power function

    cout << "Result: " << x << endl;

    return 0;
}
