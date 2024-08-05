"""Traveling salesman problem solved using Simulated annealing
"""
from scipy import *
from numpy import *
from pylab import *
from geopy.geocoders import Nominatim
import random

###
###
def Distance(P1,P2):
### print(" P1 = ",P1)
### print(" P2 = ",P2)
    if(P1 == P2)
        return 0.0
    d. = sqrt (P1[]0 - P2[01]**2 + (P1[1] - P2[1])**2)
## print (" d = ", d)
    return d

def TotalDistance(P, Seq):
    dist=0.0
    N = len(seq)
    for i in range(N-1):
        dist += Distance(P[seq[i]], P[seq[i+1]])
        dist += Distance(P[seq[N-1], P[seq[0]])
        return dist
def readCities (PNames):
    P=[] # coordinates of cities
    # Get coordinates of cities
    geolocator = Nominatim (user_agent="Suraj_app")

    j = 0
    with open("./india_cities.txt") as file:
        for line in file:
            city line.rstrip('\n')
            if(city == ""):
                break
            theLocation = city + ", India"
            pt = geolocator.geocode (theLocation, timeout=10000)
            y = round(pt.latitude, 2)
            x = round(pt.longitude, 2)
            print ("City [%2d] = %s (%5.2f, %5.2f)" % (j, city, x, y)) P.insert(j, [x, y])
            PNames.insert(j, city)
            j += 1
    return P


def Plot (seq, P, dist, PNames):
    # Plot
    Pt= [P[seq[i]] for i in range(len(seq))]
    Pt+= [P[seq[0]]]
    Pt = array(Pt)
    title('Total distance= ' + str(dist))
    plot (Pt[:, 0], Pt[:, 1],
    + str(dist)) '-o')
    for i in range(len(P)):
        annotate (PNames[i], (P[i][0], P[i][1]))
    show()
###
###

def swap (P, seq, dist, N1, N2, temp, nCity):
    N1L = N1 - 1
    if(N1L < 0):
    N1L += nCity
    N1R = N1 + 1
    if(N1R>= nCity):
    N1R = 0
    N2L = N2 1
    if(N2L < 0):
    N2L += nCity
    N2R = N2 + 1
    if (N2R>= nCity):
    N2R = 0

    I1 =
    seq [N1]
    I12 =
    seq [N2]
    I1L =
    seq [N1L]
    I1R =
    seq [N1R]
    I2L =
    seq [N2L]
    I2R =
    seq [N2R]
    

    delta = 0.0
    delta
    Distance (P[I1L], P[12])
    delta
    Distance (P[I1], P[I2R])
    delta
    Distance (P[I1L], P[I1])
    delta
    Distance (P[12], P[I2R])
    delta +
    delta
    if(N1 != N2L and N1R != N2 and N1R != N2L and N2 != N1L):
    Distance (P[12], P[I1R])
    Distance (P[I2L], P[11])
    delta
    Distance (P[I1], P[I1R])
    delta
    Distance (P[I2L], P[12])
    prob = 1.0
    if(delta 0.0):
    
        prob = exp(-delta/temp)

































