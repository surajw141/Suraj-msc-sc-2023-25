#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <NTL/ZZ.h>
#include <vector>
#include <string>

using namespace NTL;

class ElGamal
{
public:
    ZZ q, g, h, key, p;

    ElGamal();
    //     ZZ gcd(ZZ a, ZZ b);
    ZZ gen_key(ZZ q);
    ZZ power(ZZ a, ZZ b, ZZ c);
    //     std::vector<ZZ> encrypt(const std::string &msg);
    //     std::string decrypt(const std::vector<ZZ> &en_msg);

    // private:
    ZZ generate_random_prime(ZZ min, ZZ max);
};

#endif // ELGAMAL_H
