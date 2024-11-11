import math
import random
from matplotlib import pyplot as plt
from geopy.geocoders import Nominatim
import numpy as np

# Function to compute Euclidean distance between two points
def compute_distance(point1, point2):
    return math.sqrt((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2)

# Function to calculate the total distance for a given sequence of cities
def calculate_total_distance(points, sequence):
    total_distance = 0.0
    num_points = len(sequence)
    for i in range(num_points - 1):
        total_distance += compute_distance(points[sequence[i]], points[sequence[i + 1]])
    total_distance += compute_distance(points[sequence[num_points - 1]], points[sequence[0]])  # Complete the loop
    return total_distance

# Function to load city coordinates
def load_cities(city_names):
    coordinates = []  # coordinates of cities
    geolocator = Nominatim(user_agent="TravelApp")
    index = 0
    with open("india_cities.txt") as file:
        for line in file:
            city_name = line.rstrip('\n')
            if city_name == "":
                break
            location = city_name + ", India"
            location_data = geolocator.geocode(location, timeout=10000)
            if location_data:
                latitude = round(location_data.latitude, 4)
                longitude = round(location_data.longitude, 4)
                print(f"City [{index}] = {city_name} ({longitude:.4f}, {latitude:.4f})")
                coordinates.append([longitude, latitude])  # Store longitude, latitude
                city_names.append(city_name)
                index += 1
            else:
                print(f"Location for {city_name} not found.")
    return coordinates

# Function to display the plot of cities and the best tour found
def display_plot(sequence, points, total_dist, city_names):
    path_points = [points[sequence[i]] for i in range(len(sequence))]
    path_points.append(points[sequence[0]])  # Close the loop
    path_points = np.array(path_points)

    plt.figure(figsize=(10, 8))
    plt.title(f'Total distance = {total_dist:.2f}')

    # Plot the path with longitude on x-axis and latitude on y-axis
    plt.plot(path_points[:, 0], path_points[:, 1], '-o', label='Path')

    # Annotate the cities on the plot (longitude on x-axis, latitude on y-axis)
    for i in range(len(points)):
        plt.annotate(city_names[i], (points[i][0], points[i][1]), textcoords="offset points", xytext=(0, 10), ha='center')

    # Set axis labels
    plt.xlabel("Longitude")
    plt.ylabel("Latitude")
    
    # Set aspect ratio to be equal
    plt.gca().set_aspect('equal', adjustable='box')

    # Optionally set limits based on your data
    plt.xlim(min(points[:, 0]) - 1, max(points[:, 0]) + 1)  # Longitude on x-axis
    plt.ylim(min(points[:, 1]) - 1, max(points[:, 1]) + 1)  # Latitude on y-axis

    plt.grid(True)
    plt.legend()
    plt.show()

# Ant Colony Optimization solver for TSP
class SolveTSPUsingACO:
    class Edge:
        def __init__(self, a, b, weight, initial_pheromone):
            self.a = a
            self.b = b
            self.weight = weight
            self.pheromone = initial_pheromone

    class Ant:
        def __init__(self, alpha, beta, num_nodes, edges):
            self.alpha = alpha
            self.beta = beta
            self.num_nodes = num_nodes
            self.edges = edges
            self.tour = None
            self.distance = 0.0

        def _select_node(self):
            roulette_wheel = 0.0
            unvisited_nodes = [node for node in range(self.num_nodes) if node not in self.tour]
            heuristic_total = 0.0
            for unvisited_node in unvisited_nodes:
                heuristic_total += self.edges[self.tour[-1]][unvisited_node].weight
            for unvisited_node in unvisited_nodes:
                roulette_wheel += pow(self.edges[self.tour[-1]][unvisited_node].pheromone, self.alpha) * \
                                  pow((heuristic_total / self.edges[self.tour[-1]][unvisited_node].weight), self.beta)
            random_value = random.uniform(0.0, roulette_wheel)
            wheel_position = 0.0
            for unvisited_node in unvisited_nodes:
                wheel_position += pow(self.edges[self.tour[-1]][unvisited_node].pheromone, self.alpha) * \
                                  pow((heuristic_total / self.edges[self.tour[-1]][unvisited_node].weight), self.beta)
                if wheel_position >= random_value:
                    return unvisited_node

        def find_tour(self):
            self.tour = [random.randint(0, self.num_nodes - 1)]
            while len(self.tour) < self.num_nodes:
                self.tour.append(self._select_node())
            return self.tour

        def get_distance(self):
            self.distance = 0.0
            for i in range(self.num_nodes):
                self.distance += self.edges[self.tour[i]][self.tour[(i + 1) % self.num_nodes]].weight
            return self.distance

    def __init__(self, mode='ACS', colony_size=10, elitist_weight=1.0, min_scaling_factor=0.001, alpha=1.0, beta=3.0,
                 rho=0.1, pheromone_deposit_weight=1.0, initial_pheromone=1.0, steps=100, nodes=None, labels=None):
        self.mode = mode
        self.colony_size = colony_size
        self.elitist_weight = elitist_weight
        self.min_scaling_factor = min_scaling_factor
        self.rho = rho
        self.pheromone_deposit_weight = pheromone_deposit_weight
        self.steps = steps
        self.num_nodes = len(nodes)
        self.nodes = nodes
        self.labels = labels if labels is not None else range(1, self.num_nodes + 1)
        self.edges = [[None] * self.num_nodes for _ in range(self.num_nodes)]
        for i in range(self.num_nodes):
            for j in range(i + 1, self.num_nodes):
                self.edges[i][j] = self.edges[j][i] = self.Edge(i, j, compute_distance(self.nodes[i], self.nodes[j]), initial_pheromone)
        self.ants = [self.Ant(alpha, beta, self.num_nodes, self.edges) for _ in range(self.colony_size)]
        self.global_best_tour = None
        self.global_best_distance = float("inf")

    def _add_pheromone(self, tour, distance, weight=1.0):
        pheromone_to_add = self.pheromone_deposit_weight / distance
        for i in range(self.num_nodes):
            self.edges[tour[i]][tour[(i + 1) % self.num_nodes]].pheromone += weight * pheromone_to_add

    def _acs(self):
        for step in range(self.steps):
            for ant in self.ants:
                self._add_pheromone(ant.find_tour(), ant.get_distance())
                if ant.distance < self.global_best_distance:
                    self.global_best_tour = ant.tour
                    self.global_best_distance = ant.distance
            for i in range(self.num_nodes):
                for j in range(i + 1, self.num_nodes):
                    self.edges[i][j].pheromone *= (1.0 - self.rho)

    def run(self):
        print(f'Started : {self.mode}')
        self._acs()
        print(f'Ended : {self.mode}')
        print(f'Sequence : <- {" - ".join(self.labels[i] for i in self.global_best_tour)} ->')
        print(f'Total distance travelled to complete the tour : {round(self.global_best_distance, 4)}\n')

    def plot(self):
        x = [self.nodes[i][0] for i in self.global_best_tour]  # Longitude for x-axis
        x.append(x[0])
        y = [self.nodes[i][1] for i in self.global_best_tour]  # Latitude for y-axis
        y.append(y[0])
        plt.plot(x, y, '-o')
        plt.title(f'Total distance = {self.global_best_distance:.2f}')
        plt.show()

# Example usage
if __name__ == '__main__':
    city_names = []
    coordinates = load_cities(city_names)

    tsp_solver = SolveTSPUsingACO(mode='ACS', nodes=coordinates, labels=city_names)
    tsp_solver.run()
    tsp_solver.plot()
