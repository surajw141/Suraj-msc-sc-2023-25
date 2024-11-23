#include <iostream>
#include "ecc.h"     // Header for ECC operations
#include "elgamal.h" // Header for key generation, encryption, and decryption

using namespace std;

int main()
{
    ZZ privateKeySender, privateKeyReceiver;
    Point publicKeyReceiver, publicKeySender;

    // Generate keys for the sender and receiver
    generateKeys(privateKeySender, publicKeySender);
    generateKeys(privateKeyReceiver, publicKeyReceiver);

    // Example message to be encrypted (point on the curve)
    Point message = {conv<ZZ>("6"), conv<ZZ>("19")}; // Example point M = (6, 19)

    // Sender encrypts the message using the receiver's public key
    ZZ r = conv<ZZ>("7"); // Random integer for encryption
    Point ciphertext1, ciphertext2;
    encrypt(ciphertext1, ciphertext2, publicKeyReceiver, message, r);

    cout << "Ciphertext 1: (" << ciphertext1.x << ", " << ciphertext1.y << ")\n";
    cout << "Ciphertext 2: (" << ciphertext2.x << ", " << ciphertext2.y << ")\n";

    // Receiver decrypts the message using their private key
    Point decryptedMessage = decrypt(ciphertext1, ciphertext2, privateKeyReceiver);

    cout << "Decrypted Message: (" << decryptedMessage.x << ", " << decryptedMessage.y << ")\n";

    return 0;
}
