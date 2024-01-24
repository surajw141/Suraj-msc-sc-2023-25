import sys

def find_largest_and_smallest_power_of_10():
    largest = 0
    smallest = 0
    n = 0
    while True:
        try:
            x = 10 ** n
            if x > sys.float_info.max:
                largest = n - 1
                break
            n += 1
        except OverflowError:
            largest = n - 1
            break
    n = 0
    while True:
        try:
            x = 10 ** -n
            if x < sys.float_info.min:
                smallest = -n + 1
                break
            n += 1
        except OverflowError:
            smallest = -n + 1
            break
    return (largest, smallest)

result = find_largest_and_smallest_power_of_10()
print(f"The largest (positive) power of 10 of a single precision floating point that can be stored in this computer is 10^{result[0]}")
print(f"The smallest (negative) power of 10 of a single precision floating point that can be stored in this computer is 10^{result[1]}")
