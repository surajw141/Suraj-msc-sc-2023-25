#include "elgamal.h"

// Key Generation (Private and Public Keys)
void generateKeys(ZZ &privateKey, Point &publicKey)
{
    privateKey = conv<ZZ>("6");                                            // Example private key (randomly generated in real apps)
    publicKey = multiplyPoint({conv<ZZ>("2"), conv<ZZ>("4")}, privateKey); // G = (2, 4) as the base point
}

// Encryption using ElGamal (Elliptic Curve)
void encrypt(Point &ciphertext1, Point &ciphertext2, Point publicKey, Point message, ZZ r)
{
    // Compute C1 = r * G (random point)
    ciphertext1 = multiplyPoint({conv<ZZ>("2"), conv<ZZ>("4")}, r); // G = (2, 4) as the base point

    // Compute C2 = M + r * P (message + r * publicKey)
    ciphertext2 = addPoints(message, multiplyPoint(publicKey, r));
}

// Decryption using ElGamal (Elliptic Curve)
Point decrypt(Point ciphertext1, Point ciphertext2, ZZ privateKey)
{
    // Identity point (point at infinity)
    Point result = {conv<ZZ>("0"), conv<ZZ>("0")}; // Use NTL::ZZ initialization for result

    // Compute r * d * G = privateKey * ciphertext1
    Point sharedSecret = multiplyPoint(ciphertext1, privateKey);

    // M = C2 - r * P (recover the original message)
    result = addPoints(ciphertext2, multiplyPoint(sharedSecret, p - 1)); // Subtract shared secret (equivalent to adding the negative)

    return result;
}
