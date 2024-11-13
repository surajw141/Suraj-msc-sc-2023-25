#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 13 11:51:08 2024

@author: suraj
"""

def nraphson(fn, x, tol = 0.0001, maxiter = 1000):
    for i in range(maxiter):
        xnew = x - fn[0](x)/fn[1](x)
        if abs(xnew - x) < tol: break
        x = xnew
    return xnew, i

y = [lambda x : 2*x**3 - 9.5*x + 7.5, lambda x: 6*x**2 - 9.5]

x, n = nraphson(y,5)

print("The root is %f in %d iterations." % (x,n))


#the root is 1.500000 at 7 iterations.