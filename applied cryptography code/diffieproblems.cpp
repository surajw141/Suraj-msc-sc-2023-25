#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ modular_exponentiation(const ZZ &a, const ZZ &e, const ZZ &n)
{
    if (e == 0)
        return ZZ(1);
    long k = NumBits(e);
    ZZ res;
    res = 1;
    for (long i = k - 1; i >= 0; i--)
    {
        res = (res * res) % n;
        if (bit(e, i) == 1)
            res = (res * a) % n;
    }
    if (e < 0)
        return InvMod(res, n);
    else
        return res;
}

int main()
{
    ZZ p = to_ZZ(163);
    ZZ g = to_ZZ(2);
    ZZ x = to_ZZ(130);
    ZZ h = to_ZZ(119);
    ZZ a = to_ZZ(140);
    ZZ b = to_ZZ(34);

    // Calculate Alice's shared secret key
    ZZ alice_secret = modular_exponentiation(b, x, p);

    // Calculate Bob's shared secret key
    ZZ bob_secret = modular_exponentiation(a, h, p);

    cout << "Alice's shared secret key: " << alice_secret << endl;
    cout << "Bob's shared secret key: " << bob_secret << endl;

    return 0;
}