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
    if(P1 == P2):
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


    rndm random.random()
        if (rndm prob):
        dist += delta
        seq [N1] = I2
        seq [N2] = [1
        dif abs(dist TotalDistance (P, seq)) 
        if(dif*dist > 0.01):
            dist TotalDistance (P, seq) 
            print("%s\n" %("in SWAP -->"))
            print("N1-%3d N2=%3d N1L=%3d N1R=%3d N2L=%3d N2R = % 3d \n" % (N1,
N2, N1L, N1R, N2L, N2R) )
            print("11-%3d 12-%3d I1L=%3d I1R=%3d I2L=%3d I2R=%3d \n" % (I1,
12, I1L, I1R, I2L, I2R) )
delta, prob, Indm) )
            print("T= %f D= %f delta= %f p= %f_rn= %f\n" % (temp, dist,
            print (seq)
            print("%s\n" % ("") )
            input("Press Enter to continue...") 
            input("Press Enter to continue...")
    return dist, True
else:
    return dist, False
###
def reverse(P, seq, dist, N1, N2, temp, nCity):
    N1L = N1 - 1
if(N1L0):
    N1L += nCity
    N2R = N2 + 1
if (N2R >= nCity):
    N2R = 0
    delta = 0.0
if( (N1 != N2R) and (N2 != N1L) ):
else:
delta
=
Distance (P[seq [N1L]], P[seq [N2]]) \ + Distance (P[seq [N1]], P[seq[N2R]]) \ Distance (P[seq [N1L]], P[seq [N1]]) \ Distance (P[seq[N2]], P[seq [N2R]])
return dist, False
prob = 1.0
if (delta > 0.0):
prob
=
exp(-delta/temp)
rndm random.random()
if (rndm prob):
dist delta
i N1
j
1 = N2
while(i < j):
dif
u = seq[i]
seq[i] = seq[j]
seq[j] = u
i += 1
j
1
abs(dist TotalDistance (P, seq))
-
if (dif dist > 0.01):
print("in REVERSE N1L=%3d N2R=%3d \n" % (N1L, N2R) )
print("N1-%3d N2=%3d T= %f D= %f delta = %f p= %f In= %f\n" %
(N1, N2, temp, dist, delta, prob, Indm) )
##
print(seq) print()
raw_input("Press Enter to continue...")
input("Press Enter to continue...")
return dist, True
else:
return dist, False
###
if
_name_ '__main__':
PNames = [] # names of cities
P = readCities (PNames)
nCity = len(P)
maxTsteps 250 fCool 0.9 maxSwaps maxAccepted
2000
=
# Number of cities to visit
# Temperature is lowered maxTsteps times
# Factor to multiply temperature at each cooling step # Number of swaps at constant temperature
10*nCity # Number of accepted steps at constant temperature
seq= arange(0, nCity, 1)
dist TotalDistance (P, seq)
temp 10.0 dist
print("\n\n")
print(seq)
# Starting temperature - has to be high enough
print("\n nCity= %3d dist = %f temp= %f \n" % (nCity, dist, temp) ) raw_input("Press Enter to continue...")
input("Press Enter to continue...")
Plot (seq, P, dist, PNames)


old Dist = 0.0
convergenceCount=0
fort in range(1, maxTsteps+1):
if(temp 1.0e-6):
break
accepted = 0
iteration = 0
while((iteration <= maxSwaps) and (accepted < maxAccepted) ): while(iteration <= maxSwaps):
N1 = -1
while (N10 or N1 >= nCity):
N1 = ((int) (random.random() Ν1
*
1000.0)) % nCity
N2 = -1 while (N2 <
N2
or N2 >= nCity or N2 = ((int) (random.random()
N1):
1000.0)) % nCity

if (N2 < N1):
##
N1= N1 + N2
N2 = N1 N2
-
N1 = N1 - N2
print (iteration, "N", N1, N2)
chk random. uniform(0, 1)
if( (chk<0.5) and (N1+1 != N2) and (N1 != ((N2+1) % nCity)) ): dist, flag = swap(P, seq, dist, N1, N2, temp, nCity)
else:
if(flag):
dist, flag = reverse (P, seq, dist, N1, N2, temp, nCity)
accepted + 1
iteration + 1
##dist TotalDistance (P, seq)
print("Iteration: %d temp=%f dist=%f" % (t, temp, dist))
print("seg = ")

print( Iteration. %0 temp=%1 UIST=%| print("seq = ")
set_printoptions (precision=3)
print(seq)
print("%c%c" % ('\n', '\n'))
if (abs (dist oldDist) < 1.0e-4):
convergenceCount + 1
else:
convergenceCount = 0
if(convergenceCount >= 4): break
temp, ars
if((%25) == 0):
Plot(seq, P, dist, PNames).
temp fCool
oldDist dist
Plot (seq, P, dist, PNames)






























