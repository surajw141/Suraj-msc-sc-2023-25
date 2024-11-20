def nraphson(fn, x, tol=0.000001, h=1e-5):
    i = 0  # To keep track of the iteration count
    while True:
        # Use forward difference to approximate the derivative
        derivative = (fn(x + h) - fn(x)) / h
        xnew = x - fn(x) / derivative
        if abs(xnew - x) < tol:
            break
        x = xnew
        i += 1  # Increment iteration count
    return xnew, i

# Define the function
y = lambda x: 2*x**3 + 9.5*x + 7.5

# Initial guess
x, n = nraphson(y, 5)

# Print the result
print("The root is %f in %d iterations." % (x, n))
