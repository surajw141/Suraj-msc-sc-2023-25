import random

def find_largest_and_smallest(n):
    largest = float('-inf')  # Initialize largest with negative infinity
    smallest = float('inf')  # Initialize smallest with positive infinity

    while n > 0:
        r = random.randint(-2147483648, +2147483647)

        if r >= n:
            largest = r
        elif r <= n:
            smallest = r

        n -= 1

    return (largest, smallest)

# Example usage
result = find_largest_and_smallest(10)
print(result)
