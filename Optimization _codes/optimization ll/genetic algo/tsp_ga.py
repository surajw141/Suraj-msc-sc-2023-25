import random
import numpy as np
import operator
from math import sqrt
from geopy.geocoders import Nominatim
import matplotlib.pyplot as plt

class City:
    def __init__(self, x, y, name):
        self.x = x
        self.y = y
        self.name = name

    def __repr__(self):
        return f"{self.name} ({self.x},{self.y})"

    def getDistance(self, city):
        return sqrt((city.x - self.x) ** 2 + (city.y - self.y) ** 2)

def readCities(file_path):
    cityList = []
    geolocator = Nominatim(user_agent="tsp_app")
    with open(file_path, "r") as file:
        for line in file:
            city_name = line.strip()
            location = geolocator.geocode(city_name, timeout=10)
            if location:
                cityList.append(City(location.longitude, location.latitude, city_name))
    return cityList

class Fitness:
    def __init__(self, route):
        self.route = route
        self.distance = 0.0
        self.fitness = 0.0

    def routeDistance(self):
        if self.distance == 0:
            total_distance = 0
            for i in range(len(self.route)):
                from_city = self.route[i]
                to_city = self.route[(i + 1) % len(self.route)]
                total_distance += from_city.getDistance(to_city)
            self.distance = total_distance
        return self.distance

    def getFitness(self):
        if self.fitness == 0:
            self.fitness = 1 / float(self.routeDistance())
        return self.fitness

def createRoute(cityList):
    return random.sample(cityList, len(cityList))

def initialPopulation(popSize, cityList):
    return [createRoute(cityList) for _ in range(popSize)]

def rankRoutes(population):
    fitnessResults = {}
    for i in range(len(population)):
        fitnessResults[i] = Fitness(population[i]).getFitness()
    return sorted(fitnessResults.items(), key=operator.itemgetter(1), reverse=True)

def selection(popRanked, eliteSize):
    selectionResults = []
    df = np.array([fitness for _, fitness in popRanked])
    
    # Normalize the probabilities
    df = df / df.sum()
    
    # Ensure the sum of probabilities is exactly 1 due to floating-point precision issues
    if df.sum() < 1:
        df[-1] += 1 - df.sum()
    
    # Select based on the probabilities
    selectionResults = np.random.choice(len(popRanked), eliteSize, p=df)
    return selectionResults

def matingPool(population, selectionResults):
    matingpool = []
    for i in range(len(selectionResults)):
        index = selectionResults[i]
        matingpool.append(population[index])
    return matingpool

def breed(parent1, parent2):
    child = []
    geneA = int(random.random() * len(parent1))
    geneB = int(random.random() * len(parent1))
    startGene = min(geneA, geneB)
    endGene = max(geneA, geneB)

    childP1 = parent1[startGene:endGene]
    childP2 = [item for item in parent2 if item not in childP1]

    child = childP1 + childP2
    return child

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

def mutate(individual, mutationRate):
    for swapped in range(len(individual)):
        if random.random() < mutationRate:
            swapWith = int(random.random() * len(individual))

            city1 = individual[swapped]
            city2 = individual[swapWith]

            individual[swapped] = city2
            individual[swapWith] = city1
    return individual

def mutatePopulation(population, mutationRate):
    mutatedPop = []
    for ind in range(len(population)):
        mutatedInd = mutate(population[ind], mutationRate)
        mutatedPop.append(mutatedInd)
    return mutatedPop

def nextGeneration(currentGen, eliteSize, mutationRate):
    popRanked = rankRoutes(currentGen)
    selectionResults = selection(popRanked, eliteSize)
    matingpool = matingPool(currentGen, selectionResults)
    children = breedPopulation(matingpool, eliteSize)
    nextGeneration = mutatePopulation(children, mutationRate)
    return nextGeneration

def geneticAlgorithm(cityList, popSize, eliteSize, mutationRate, generations, printFitness=False):
    pop = initialPopulation(popSize, cityList)
    bestRoute = None

    for i in range(generations):
        pop = nextGeneration(pop, eliteSize, mutationRate)
        
        if printFitness:
            print(f"Generation {i} - Fitness of all individuals:")
            for idx, route in enumerate(pop):
                fitness = Fitness(route).getFitness()
                print(f"Individual {idx + 1}: Fitness = {fitness:.6f}")

        if i % 50 == 0:
            bestRoute = pop[rankRoutes(pop)[0][0]]
            distance = 1 / Fitness(bestRoute).getFitness()
            print(f"Generation {i} - Best Distance: {distance:.2f}")
            plotRoute(bestRoute, title=f"Generation {i} - Distance: {distance:.2f}")

    # Final best route
    bestRoute = pop[rankRoutes(pop)[0][0]]
    return bestRoute


def plotRoute(bestRoute, title="Route"):
    plt.figure(figsize=(10, 5))
    x = [city.x for city in bestRoute] + [bestRoute[0].x]
    y = [city.y for city in bestRoute] + [bestRoute[0].y]
    plt.plot(x, y, marker='o')
    plt.title(title)
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    cityList = readCities("india_cities.txt")
    
    popSize = 100
    eliteSize = int(0.85 * popSize)
    mutationRate = 0.04
    generations = 500

    # Call the geneticAlgorithm function, which now returns the best route
    bestRoute = geneticAlgorithm(cityList, popSize, eliteSize, mutationRate, generations)

    # Plot the final best route
    plotRoute(bestRoute, title="Final Best Route")


