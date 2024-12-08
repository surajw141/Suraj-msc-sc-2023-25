# demonstrate diffie hellman key exchange

p = int(input("Enter the value of p: "))
g = int(input("Enter the value of g: "))
x = int(input("Enter the value of x: "))

h = (g**x)%p
print("The value of h is: ", h) 

m = int(input("Enter the value of m: "))

y = int(input("Enter the value of y: "))

print("The value of y is: ", y)

s = (x**y)%p
print("The value of s is: ", s)

c1 = (g**y)%p
print("The value of c1 is: ", c1)

c2 = (m*s)%p

print("The value of c2 is: ", c2)

mi = (c1**x)%17

print("The value of mi is: ", mi)


inverse_of_mi = pow(mi, -1, 11)  # Computes 2^(-1) mod 17
m2 = c2 * inverse_of_mi  # Multiply the result by 1 (as in your expression)
#m2 = (m2)%p
print("The result is:", m2)

