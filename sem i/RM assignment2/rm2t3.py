import sys

def find_largest_and_smallest_power_of_10():
    largest = 0
    smallest = 0
    n = 0
    while True:
        try:
            x = 10 ** n
            if x > 10 ** sys.float_info.max_10_exp:
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
            if x < 10 ** sys.float_info.min_10_exp:
                smallest = -n + 1
                break
            n += 1
        except OverflowError:
            smallest = -n + 1
            break
    
    return (largest * (2**(-1023)), smallest * (2**(-1023)))

result = find_largest_and_smallest_power_of_10()
print(f"The largest (positive) power of 10 of a double precision floating point that can be stored in this computer is 10^{result[0]}")
print(f"The smallest (negative) power of 10 of a double precision floating point that can be stored in this computer is 10^{result[1]}")
