from scipy import *
from numpy import *
from pylab import *
from geopy.geocoders import Nominatim
import random

def compute_distance(point1, point2):
    if point1 == point2:
        return 0.0
    distance = sqrt((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2)
    return distance

def calculate_total_distance(points, sequence):
    total_distance = 0.0
    num_points = len(sequence)
    for i in range(num_points - 1):
        total_distance += compute_distance(points[sequence[i]], points[sequence[i + 1]])
    total_distance += compute_distance(points[sequence[num_points - 1]], points[sequence[0]])  # Complete the loop
    return total_distance

def load_cities(city_names):
    coordinates = []  # coordinates of cities
    geolocator = Nominatim(user_agent="TravelApp")
    index = 0
    with open("./india_cities.txt") as file:
        for line in file:
            city_name = line.rstrip('\n')
            if city_name == "":
                break
            location = city_name + ", India"
            location_data = geolocator.geocode(location, timeout=10000)
            latitude = round(location_data.latitude, 2)
            longitude = round(location_data.longitude, 2)
            print("City [%2d] = %s (%5.2f, %5.2f)" % (index, city_name, longitude, latitude))
            coordinates.append([longitude, latitude])
            city_names.append(city_name)
            index += 1
    return coordinates

def display_plot(sequence, points, total_dist, city_names):
    path_points = [points[sequence[i]] for i in range(len(sequence))]
    path_points.append(points[sequence[0]])  # Close the loop
    path_points = array(path_points)
    title('Total distance = ' + str(total_dist))
    plot(path_points[:, 0], path_points[:, 1], '-o')
    for i in range(len(points)):
        annotate(city_names[i], (points[i][0], points[i][1]))
    show()

def attempt_swap(points, sequence, total_dist, index1, index2, temperature, num_cities):
    left1 = index1 - 1
    if left1 < 0:
        left1 += num_cities
    right1 = index1 + 1
    if right1 >= num_cities:
        right1 = 0
    left2 = index2 - 1
    if left2 < 0:
        left2 += num_cities
    right2 = index2 + 1
    if right2 >= num_cities:
        right2 = 0

    city1 = sequence[index1]
    city2 = sequence[index2]
    city1_left = sequence[left1]
    city1_right = sequence[right1]
    city2_left = sequence[left2]
    city2_right = sequence[right2]

    delta_distance = 0.0
    delta_distance += compute_distance(points[city1_left], points[city2]) + compute_distance(points[city1], points[city2_right])
    delta_distance -= compute_distance(points[city1_left], points[city1]) + compute_distance(points[city2], points[city2_right])

    if index1 != left2 and right1 != index2 and right1 != left2 and index2 != left1:
        delta_distance += compute_distance(points[city2_left], points[city1]) + compute_distance(points[city2], points[city1_right])
        delta_distance -= compute_distance(points[city2_left], points[city2]) + compute_distance(points[city1], points[city1_right])

    probability = 1.0
    if delta_distance > 0.0:
        probability = exp(-delta_distance / temperature)

    random_value = random.random()
    if random_value < probability:
        total_dist += delta_distance
        sequence[index1], sequence[index2] = sequence[index2], sequence[index1]  # Swap cities
        difference = abs(total_dist - calculate_total_distance(points, sequence))
        if difference * total_dist > 0.01:
            total_dist = calculate_total_distance(points, sequence)  # Recalculate distance for accuracy
        return total_dist, True
    else:
        return total_dist, False

def attempt_reverse(points, sequence, total_dist, index1, index2, temperature, num_cities):
    left1 = index1 - 1
    if left1 < 0:
        left1 += num_cities
    right2 = index2 + 1
    if right2 >= num_cities:
        right2 = 0
    delta_distance = 0.0
    if (index1 != right2) and (index2 != left1):
        delta_distance = (compute_distance(points[sequence[left1]], points[sequence[index2]]) + compute_distance(points[sequence[index1]], points[sequence[right2]])
                          - compute_distance(points[sequence[left1]], points[sequence[index1]]) - compute_distance(points[sequence[index2]], points[sequence[right2]]))

    else:
        return total_dist, False
    
    probability = 1.0
    if delta_distance > 0.0:
        probability = exp(-delta_distance / temperature)
        
    random_value = random.random()
    if random_value < probability:
        total_dist += delta_distance
        i, j = index1, index2
        while i < j:
            sequence[i], sequence[j] = sequence[j], sequence[i]  # Reverse the segment
            i += 1
            j -= 1
        difference = abs(total_dist - calculate_total_distance(points, sequence))
        if difference * total_dist > 0.01:
            total_dist = calculate_total_distance(points, sequence)
        return total_dist, True
    else:
        return total_dist, False

if __name__ == '__main__':
    city_names = []  # names of cities
    coordinates = load_cities(city_names)
    num_cities = len(coordinates)  # Number of cities to visit

    max_steps = 250  # Temperature is lowered max_steps times
    cooling_factor = 0.9  # Factor to multiply temperature at each cooling step
    max_attempts = 2000
    max_accepted_steps = 10 * num_cities  # Number of accepted steps at constant temperature
    sequence = arange(0, num_cities, 1)
    total_distance = calculate_total_distance(coordinates, sequence)
    temperature = 10.0 * total_distance  # Starting temperature - has to be high enough

    print("\n\n")
    print(sequence)
    print("\n num_cities= %3d total_distance = %f temperature = %f \n" % (num_cities, total_distance, temperature))

    input("Press Enter to continue...")
    display_plot(sequence, coordinates, total_distance, city_names)

    previous_distance = 0.0
    convergence_counter = 0
    for step in range(1, max_steps + 1):
        if temperature < 1.0e-6:
            break
        accepted_steps = 0
        attempt = 0
        while attempt <= max_attempts:
            index1 = random.randint(0, num_cities - 1)
            index2 = random.randint(0, num_cities - 1)
            while index2 == index1:
                index2 = random.randint(0, num_cities - 1)

            if index2 < index1:
                index1, index2 = index2, index1

            check_value = random.uniform(0, 1)
            if (check_value < 0.5) and (index1 + 1 != index2) and (index1 != ((index2 + 1) % num_cities)):
                total_distance, successful = attempt_swap(coordinates, sequence, total_distance, index1, index2, temperature, num_cities)
            else:
                total_distance, successful = attempt_reverse(coordinates, sequence, total_distance, index1, index2, temperature, num_cities)

            if successful:
                accepted_steps += 1
            attempt += 1
        
        print("Step: %d temperature=%f total_distance=%f" % (step, temperature, total_distance))
        if abs(total_distance - previous_distance) < 1.0e-4:
            convergence_counter += 1
        else:
            convergence_counter = 0

        if convergence_counter >= 4:
            break
        if step % 25 == 0:
            display_plot(sequence, coordinates, total_distance, city_names)

        temperature *= cooling_factor
        previous_distance = total_distance

    display_plot(sequence, coordinates, total_distance, city_names)

