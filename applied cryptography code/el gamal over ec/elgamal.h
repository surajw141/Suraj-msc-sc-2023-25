#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <NTL/ZZ.h>
#include "ecc.h" // Include ECC operations

using namespace NTL;

// Function declarations for ElGamal operations
void generateKeys(ZZ &privateKey, Point &publicKey);
void encrypt(Point &ciphertext1, Point &ciphertext2, Point publicKey, Point message, ZZ r);
Point decrypt(Point ciphertext1, Point ciphertext2, ZZ privateKey);

#endif // ELGAMAL_H
