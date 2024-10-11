import random
import numpy as np
import operator
from math import sqrt
from geopy.geocoders import Nominatim
import matplotlib.pyplot as plt

# City class to hold the city's coordinates and name
class City:
    def __init__(self, x, y, name):
        self.x = x
        self.y = y
        self.name = name

    def __repr__(self):
        return f"{self.name} ({self.x},{self.y})"

    def getDistance(self, city):
        return sqrt((city.x - self.x) ** 2 + (city.y - self.y) ** 2)

# Calculate distances similar to SA
def Distance(P1, P2):
    if P1 == P2:
        return 0.0
    return sqrt((P1.x - P2.x) ** 2 + (P1.y - P2.y) ** 2)

def TotalDistance(route):
    dist = 0.0
    N = len(route)
    for i in range(N - 1):
        dist += Distance(route[i], route[i + 1])
    dist += Distance(route[-1], route[0])  # Close the loop
    return dist

# Adapted Genetic Algorithm functions
def swap(route, N1, N2):
    route[N1], route[N2] = route[N2], route[N1]

def reverse(route, N1, N2):
    while N1 < N2:
        swap(route, N1, N2)
        N1 += 1
        N2 -= 1

# Function to read cities from a file and get coordinates using geopy
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

# Fitness class to evaluate the fitness of a route
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

# Create a random route from a list of cities
def createRoute(cityList):
    return random.sample(cityList, len(cityList))

# Generate an initial population of routes
def initialPopulation(popSize, cityList):
    return [createRoute(cityList) for _ in range(popSize)]

# Rank routes according to fitness
def rankRoutes(population):
    fitnessResults = {}
    for i in range(len(population)):
        fitnessResults[i] = Fitness(population[i]).getFitness()
    return sorted(fitnessResults.items(), key=operator.itemgetter(1), reverse=True)

# Selection function to select parents for breeding
def selection(popRanked, retain_length):
    selectionResults = []
    df = np.array([fitness for _, fitness in popRanked])
    
    # Normalize the probabilities
    df = df / df.sum()
    
    # Ensure the sum of probabilities is exactly 1 due to floating-point precision issues
    if df.sum() < 1:
        df[-1] += 1 - df.sum()
    
    # Select based on the probabilities
    selectionResults = np.random.choice(len(popRanked), retain_length, p=df)
    return selectionResults

# Create mating pool from selected parents
def matingPool(population, selectionResults):
    matingpool = []
    for i in range(len(selectionResults)):
        index = selectionResults[i]
        matingpool.append(population[index])
    return matingpool

# Breed two parents to create a child route
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

# Generate a new population by breeding the mating pool
def breedPopulation(matingpool, retain_length, max_children_per_pair):
    children = []
    length = len(matingpool) - retain_length
    pool = random.sample(matingpool, len(matingpool))

    for i in range(retain_length):
        children.append(matingpool[i])

    for i in range(length):
        parent1 = pool[i]
        parent2 = pool[len(matingpool) - i - 1]
        for _ in range(max_children_per_pair):
            child = breed(parent1, parent2)
            children.append(child)
            if len(children) >= len(matingpool):
                break
        if len(children) >= len(matingpool):
            break
    return children[:len(matingpool)]

# Mutate a route by swapping cities with a certain mutation rate
def mutate(individual, mutationRate):
    for swapped in range(len(individual)):
        if random.random() < mutationRate:
            swapWith = int(random.random() * len(individual))

            city1 = individual[swapped]
            city2 = individual[swapWith]

            individual[swapped] = city2
            individual[swapWith] = city1
    return individual

# Mutate a population of routes
def mutatePopulation(population, mutationRate):
    mutatedPop = []
    for ind in range(len(population)):
        mutatedInd = mutate(population[ind], mutationRate)
        mutatedPop.append(mutatedInd)
    return mutatedPop

def nextGeneration(currentGen, eliteSize, mutationRate, max_children_per_pair):
    popRanked = rankRoutes(currentGen)
    bestRouteIndex = popRanked[0][0]  # Index of the best route
    bestRoute = currentGen[bestRouteIndex]  # Best route

    # Perform selection, breeding, and mutation
    selectionResults = selection(popRanked, eliteSize)
    matingpool = matingPool(currentGen, selectionResults)
    children = breedPopulation(matingpool, eliteSize, max_children_per_pair)
    nextGeneration = mutatePopulation(children, mutationRate)

    # Replace the worst route with the best route from the previous generation
    worstIndex = popRanked[-1][0]  # Index of the worst route
    nextGeneration[worstIndex] = bestRoute  # Ensure best route is preserved

    return nextGeneration

def geneticAlgorithm(cityList, popSize, eliteSize, mutationRate, generations, max_children_per_pair):
    pop = initialPopulation(popSize, cityList)
    bestRouteOverall = None
    minDistOverall = float('inf')
    
    for i in range(generations):
        pop = nextGeneration(pop, eliteSize, mutationRate, max_children_per_pair)
        currentBestRoute = pop[rankRoutes(pop)[0][0]]
        currentBestDist = TotalDistance(currentBestRoute)
        
        # Track the best overall distance and route
        if currentBestDist < minDistOverall:
            minDistOverall = currentBestDist
            bestRouteOverall = currentBestRoute
        
        print(f"Generation {i}: Distance = {currentBestDist}")

        # Plotting every 25 generations
        if i % 25 == 0:
            plotRoute(currentBestRoute, title=f"Generation {i} - Distance: {currentBestDist:.2f}")
    
    # Plot the best route found overall
    plotRoute(bestRouteOverall, title=f"Final Best Route - Minimum Distance: {minDistOverall:.2f}")
    print(f"\nMinimum Distance found: {minDistOverall:.2f}")
    return bestRouteOverall, minDistOverall


# Plot the best route
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

# Example usage
if __name__ == "__main__":
    cityList = readCities("india_cities.txt")
    
    popSize = 100
    eliteSize = int(0.85 * popSize)
    mutationRate = 0.04
    generations = 250
    max_children_per_pair = 2

    bestRoute, minDist = geneticAlgorithm(cityList, popSize, eliteSize, mutationRate, generations, max_children_per_pair)
    print(f"The minimum distance achieved is: {minDist:.2f}")
