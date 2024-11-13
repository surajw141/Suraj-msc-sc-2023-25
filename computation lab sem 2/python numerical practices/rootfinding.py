from scipy import optimize
g = lambda x : x**2 - 1
optimize.brentq(g,0.5, 1.5) #finds the root in the interval [0.5, 1.5]

optimize.brentq(g,-1.5, -0.5)

f = lambda x: np.sin(np.pi*x) - x
optimize.brentq(f,-0.1, 0.1)