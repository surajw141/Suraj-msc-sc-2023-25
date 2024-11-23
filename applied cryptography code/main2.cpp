#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

void fun()
{
    ZZ_p c, d;
}

ZZ classname::DLP_bruteforce(ZZ_p h, ZZ_p g, int x)
{
    ZZ_p temp;
    for (int i = 1; i < x; i++)
    {
        power(temp, g, i);
        if (temp == h)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    zz p = conv<ZZ>("101");

    ZZ_p::init(p);
    ZZ_p a, b;

    // a = conv<ZZ_p>("5");
    // cout << "\n a :: "

    // G, g^3 = h
    ZZ_p g = conv<ZZ_p>("2");
    int x = (101 / 2);
    ZZ_p h;
    power(h, g, x); // h = g^x

    cout << "\n h :: " << g << "\t h :: " << h << endl;

    // bruteforce attack on DLP

    for (int i = 1; i < x; i++)
    {
        ZZ_p temp;
        power(temp, g, i);
        if (temp == h)
        {
            cout << "\n Found :: " << i << endl;
            flag = true;
            break;
        }
    }
    if (!flag)
        return 0;
}