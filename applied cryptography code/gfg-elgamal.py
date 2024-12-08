from math import pow

# Fixed values for ElGamal encryption
p = 191  # Prime modulus
g = 19    # Base (generator)
x = 170   # Private key of the receiver (receiver's private key)
h = 121   # Public key of the receiver (h = g^x mod p)
msg = [105]  # Message to be encrypted (assuming it's a list of integers for simplicity)

# Modular exponentiation (efficient method)
def power(a, b, c):
    x = 1
    y = a
    while b > 0:
        if b % 2 != 0:
            x = (x * y) % c
        y = (y * y) % c
        b = int(b / 2)
    return x % c

# Find modular inverse of a number (using Extended Euclidean Algorithm)
def mod_inverse(a, p):
    t, new_t = 0, 1
    r, new_r = p, a
    while new_r != 0:
        quotient = r // new_r
        t, new_t = new_t, t - quotient * new_t
        r, new_r = new_r, r - quotient * new_r
    if r > 1:
        return None  # No inverse exists
    if t < 0:
        t = t + p
    return t

# Asymmetric encryption
def encrypt(msg, q, h, g):
    en_msg = []

    # Generate a random k for encryption (this should normally be random)
    k = 7  # Fixed for simplicity
    
    # Calculate c1 = g^k mod p and c2 = m * h^k mod p
    c1 = power(g, k, q)
    c2 = [(m * power(h, k, q)) % q for m in msg]
   
    print("g^k used (c1):", c1)
    print("h^k used:", power(h, k, q))

    return c1, c2

# Decryption: m = c2 * (c1^x)^(-1) mod p
def decrypt(c1, c2, key, q):
    dr_msg = []
    # Calculate c1^x mod p
    c1_x = power(c1, key, q)
    # Find the modular inverse of c1^x mod p
    c1_x_inv = mod_inverse(c1_x, q)
    
    # Decrypt each cipher pair
    for c in c2:
        m = (c * c1_x_inv) % q
        dr_msg.append(m)
    
    return dr_msg

# Driver code
def main():
    print("Original Message:", msg)

    q = p  # Use the fixed prime p as q for simplicity

    # Calculate receiver's public key h = g^x mod p
    key = x  # Receiver's private key
    h = power(g, key, q)  # h = g^x mod p
    print("g used:", g)
    print("g^x (receiver's public key) used:", h)

    # Encrypt the message
    c1, c2 = encrypt(msg, q, h, g)

    # Decrypt the message
    decrypted_msg = decrypt(c1, c2, key, q)
    print("Decrypted Message:", decrypted_msg)

if __name__ == '__main__':
    main()
