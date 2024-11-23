#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;

int main()
{
    ZZ p = conv<ZZ>("101");
    ZZ_p::init(p); // Ensure the modulus is initialized before any ZZ_p operations

    // Add debug statements to ensure the program is working as expected
    cout << "Modulus p: " << p << endl;

    ZZ_p g = conv<ZZ_p>(2); // Convert integer to ZZ_p type
    cout << "Generator g: " << g << endl;

    int x = 101 / 2;

    ZZ_p h;
    power(h, g, x); // h = g^x
    cout << "h = g^" << x << " = " << h << endl;

    return 0;
}
