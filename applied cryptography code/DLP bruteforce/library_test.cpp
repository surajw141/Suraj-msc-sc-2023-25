#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <iostream>

using namespace NTL;
using namespace std;

int main()
{
    ZZ p = conv<ZZ>("101");

    cout << "Before ZZ_p::init()" << endl;
    ZZ_p::init(p);
    cout << "After ZZ_p::init()" << endl;

    ZZ_p g = conv<ZZ_p>(2);
    ZZ_p h;

    cout << "Before power(h, g, 50)" << endl;
    power(h, g, 50); // Testing a simple power operation
    cout << "After power(h, g, 50)" << endl;

    cout << "g = " << g << "\th = " << h << endl;

    return 0;
}
