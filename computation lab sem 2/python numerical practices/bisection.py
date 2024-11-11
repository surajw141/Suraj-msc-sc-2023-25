import numpy as np
def my_bisection(f, a, b, tol):
# approximates a root, R, of f bounded
# by a and b to within tolerance
# | f(m) | < tol with m being the midpoint
# between a and b. Recursive implementation
# check if a and b bound a root
    if np.sign(f(a)) == np.sign(f(b)):
        raise Exception(
    "The scalars a and b do not bound a root")
# get midpoint
    m = (a + b)/2
    if np.abs(f(m)) < tol:
# stopping condition, report m as root
        return m
    elif np.sign(f(a)) == np.sign(f(m)):
# case where m is an improvement on a.
# Make recursive call with a = m
        return my_bisection(f, m, b, tol)
    elif np.sign(f(b)) == np.sign(f(m)):
# case where m is an improvement on b.
# Make recursive call with b = m
        return my_bisection(f, a, m, tol)


def f(x):
    return x**2 - 4  # This function has roots at x = -2 and x = 2

# Choose bounds where the function changes sign
a = 1  # f(1) = -3
b = 3  # f(3) = 5

# Set the tolerance
tol = 1e-5

# Call the bisection method
root = my_bisection(f, a, b, tol)

print("Root found:", root)