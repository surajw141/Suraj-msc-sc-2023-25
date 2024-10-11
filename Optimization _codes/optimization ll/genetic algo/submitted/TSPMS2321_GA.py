
import random
import math
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from geopy.geocoders import Nominatim

# City class
class City:
    def __init__(self, x, y, name):
        self.x = x
        self.y = y
        self.name = name

    def __repr__(self):
        return self.name + " (" + str(self.x) + "," + str(self.y) + ")"

    def getDistance(self, city):
        return math.sqrt((city.x - self.x) ** 2 + (city.y - self.y) ** 2)

# Fitness class
class Fitness:
    def __init__(self, route):
        self.route = route
        self.distance = 0.0
        self.fitness = 0.0

    def routeDistance(self):
        if self.distance == 0:
            self.distance = sum([self.route[i].getDistance(self.route[i + 1]) for i in range(len(self.route) - 1)])
            self.distance += self.route[-1].getDistance(self.route[0])  # Complete the loop
        return self.distance

    def routeFitness(self):
        if self.fitness == 0:
            self.fitness = 1 / float(self.routeDistance())
        return self.fitness

# Create a random route
def createRoute(cityList):
    route = random.sample(cityList, len(cityList))
    return route

# Initialize population
def initialPopulation(popSize, cityList):
    population = [createRoute(cityList) for _ in range(popSize)]
    return population

# Rank routes based on fitness
def rankRoutes(population):
    fitnessResults = {i: Fitness(population[i]).routeFitness() for i in range(len(population))}
    return sorted(fitnessResults.items(), key=lambda x: x[1], reverse=True)

# Selection process
def selection(popRanked, eliteSize):
    selectionResults = []
    df = pd.DataFrame(np.array(popRanked), columns=["Index", "Fitness"])
    df['cum_sum'] = df.Fitness.cumsum()
    df['cum_perc'] = 100 * df.cum_sum / df.Fitness.sum()

    for i in range(eliteSize):
        selectionResults.append(popRanked[i][0])
    for _ in range(len(popRanked) - eliteSize):
        pick = 100 * random.random()
        for i in range(len(popRanked)):
            if pick <= df.iat[i, 3]:
                selectionResults.append(popRanked[i][0])
                break
    return selectionResults

# Create mating pool
def matingPool(population, selectionResults):
    matingpool = [population[i] for i in selectionResults]
    return matingpool

# Breed two parents to create a child
def breed(parent1, parent2):
    child = []
    childP1 = []
    childP2 = []

    geneA = int(random.random() * len(parent1))
    geneB = int(random.random() * len(parent1))

    startGene = min(geneA, geneB)
    endGene = max(geneA, geneB)

    for i in range(startGene, endGene):
        childP1.append(parent1[i])

    childP2 = [item for item in parent2 if item not in childP1]

    child = childP1 + childP2
    return child

# Perform crossover on the mating pool
def breedPopulation(matingpool, eliteSize):
    children = []
    length = len(matingpool) - eliteSize
    pool = random.sample(matingpool, len(matingpool))

    for i in range(eliteSize):
        children.append(matingpool[i])

    for i in range(length):
        child = breed(pool[i], pool[len(matingpool) - i - 1])
        children.append(child)
    return children

# Mutate a single route
def mutate(individual, mutationRate):
    for swapped in range(len(individual)):
        if random.random() < mutationRate:
            swapWith = int(random.random() * len(individual))

            city1 = individual[swapped]
            city2 = individual[swapWith]

            individual[swapped] = city2
            individual[swapWith] = city1
    return individual

# Mutate the entire population
def mutatePopulation(population, mutationRate):
    mutatedPop = [mutate(population[i], mutationRate) for i in range(len(population))]
    return mutatedPop

# Evolve population to the next generation
def nextGeneration(currentGen, eliteSize, mutationRate):
    popRanked = rankRoutes(currentGen)
    selectionResults = selection(popRanked, eliteSize)
    matingpool = matingPool(currentGen, selectionResults)
    children = breedPopulation(matingpool, eliteSize)
    nextGeneration = mutatePopulation(children, mutationRate)
    return nextGeneration

# Genetic Algorithm with progress tracking
def geneticAlgorithm(cityList, popSize, eliteSize, mutationRate, generations):
    pop = initialPopulation(popSize, cityList)
    print("Initial distance: " + str(1 / rankRoutes(pop)[0][1]))

    progress = [1 / rankRoutes(pop)[0][1]]  # Store initial distance

    for i in range(0, generations):
        pop = nextGeneration(pop, eliteSize, mutationRate)
        bestDist = 1 / rankRoutes(pop)[0][1]
        progress.append(bestDist)
        print(f"Generation {i+1}: Distance = {bestDist}")

    print("Final distance: " + str(1 / rankRoutes(pop)[0][1]))
    bestRouteIndex = rankRoutes(pop)[0][0]
    bestRoute = pop[bestRouteIndex]

    plt.plot(progress)
    plt.ylabel('Distance')
    plt.xlabel('Generation')
    plt.title('TSP Genetic Algorithm Optimization')
    plt.show()

    return bestRoute

# Read cities from file and get their coordinates
def readCities(PNames):
    P = []  # coordinates of cities
    geolocator = Nominatim(user_agent="Suraj_app")
    j = 0
    with open("./india_cities.txt") as file:
        for line in file:
            city = line.rstrip('\n')
            if city == "":
                break
            theLocation = city + ", India"
            pt = geolocator.geocode(theLocation, timeout=10000)
            y = round(pt.latitude, 2)
            x = round(pt.longitude, 2)
            print("City [%2d] = %s (%5.2f, %5.2f)" % (j, city, x, y))
            P.insert(j, [x, y])
            PNames.insert(j, city)
            j += 1
    return P

# Utility functions to integrate with the provided code
def convertCitiesToCityObjects(P, PNames):
    cityList = [City(P[i][0], P[i][1], PNames[i]) for i in range(len(P))]
    return cityList

def PlotGA(route, dist, PNames):
    Pt = [(city.x, city.y) for city in route]
    Pt.append((route[0].x, route[0].y))  # Complete the loop by returning to the first city
    Pt = np.array(Pt)
    plt.title('Total distance= ' + str(dist))
    plt.plot(Pt[:, 0], Pt[:, 1], '-o')
    for i in range(len(route)):
        plt.annotate(route[i].name, (route[i].x, route[i].y))
    plt.show()

if __name__ == "__main__":
    PNames = []  # Names of cities
    P = readCities(PNames)
    cityList = convertCitiesToCityObjects(P, PNames)

    popSize = 100  # Population size
    eliteSize = 20  # Elite selection size
    mutationRate = 0.01  # Mutation rate
    generations = 300  # Number of generations

    bestRoute = geneticAlgorithm(cityList, popSize, eliteSize, mutationRate, generations)
    bestDist = 1 / Fitness(bestRoute).routeFitness()
    PlotGA(bestRoute, bestDist, PNames)
