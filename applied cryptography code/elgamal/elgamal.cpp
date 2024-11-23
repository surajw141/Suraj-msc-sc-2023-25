#include "elgamal.h"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

using namespace std;
using namespace NTL;

ElGamal::ElGamal()
{
    q = generate_random_prime(conv<ZZ>(pow(10, 20)), conv<ZZ>(pow(10, 50)));
    g = RandomBnd(q - 2) + 2; // g is a random number in the range [2, q-1]
    key = gen_key(q);
    h = power(g, key, q);
}

// ZZ ElGamal::gcd(ZZ a, ZZ b)
// {
//     if (a < b)
//     {
//         return gcd(b, a);
//     }
//     else if (a % b == 0)
//     {
//         return b;
//     }
//     else
//     {
//         return gcd(b, a % b);
//     }
// }

ZZ ElGamal::gen_key(ZZ q)
{
    ZZ key = RandomBnd(q - 1) + 1; // key is a random number in the range [1, q-1]
    // while (gcd(q, key) != 1)
    // {
    //     key = RandomBnd(q - 1) + 1;
    // }
    return key;
}

ZZ ElGamal::power(ZZ a, ZZ b, ZZ c)
{
    ZZ x = conv<ZZ>(1);
    ZZ y = a;

    while (b > 0)
    {
        if (b % 2 != 0)
        {
            x = (x * y) % c;
        }
        y = (y * y) % c;
        b /= 2;
    }
    return x % c;
}

ZZ ElGamal::generate_random_prime(ZZ min, ZZ max)
{
    ZZ prime;

    // Generate a random number in the range [min, max)
    ZZ range = max - min;
    do
    {
        prime = RandomBnd(range) + min;
    } while (!ProbPrime(prime));

    return prime;
}

// std::vector<ZZ> ElGamal::encrypt(const std::string &msg)
// {
//     std::vector<ZZ> en_msg;
//     ZZ k = gen_key(q); // Private key for sender
//     ZZ s = power(h, k, q);
//     p = power(g, k, q);

//     for (char c : msg)
//     {
//         en_msg.push_back(s * conv<ZZ>(c));
//     }

//     cout << "g^k used : " << p << endl;
//     cout << "g^ak used : " << s << endl;

//     return en_msg;
// }

// std::string ElGamal::decrypt(const std::vector<ZZ> &en_msg)
// {
//     std::string dr_msg;
//     ZZ h_inv = power(p, key, q);

//     for (ZZ c : en_msg)
//     {
//         dr_msg.push_back(conv<char>(c / h_inv));
//     }

//     return dr_msg;
//}
