#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 13 11:26:08 2024

@author: suraj
"""

import numpy as np
import matplotlib.pyplot as plt

x = np.array([20.5,32.7,51,73.2,95.7])
y = np.array([765,826,873,942,1032])
N = np.size(x)

#create 2x2 linear system
t = np.array([[np.sum(np.pow(x,2)),np.sum(x)],
              [np.sum(x), N]])

c = np.array([np.sum([xi*yi])])