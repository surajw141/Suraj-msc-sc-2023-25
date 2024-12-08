def multiplicative_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        # q is quotient
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    # Make x1 positive
    if x1 < 0:
        x1 += m0
    return x1

a = 2
m = 11
inverse = multiplicative_inverse(a, m)
print("Multiplicative inverse of", a, "modulo", m, "is:", inverse)
