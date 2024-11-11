import numpy as np
f = lambda x: x**2 - 2
f_prime = lambda x: 2*x
newton_raphson = 1.4 - f(1.4)/f_prime(1.4)
print("newton_raphson =", newton_raphson)
print("sqrt(2) =", np.sqrt(2))
