# demonstrate diffie hellman key exchange

p = int(input("Enter the value of p: "))
g = int(input("Enter the value of g: "))
a = int(input("Enter the value of a: "))
b = int(input("Enter the value of b: "))


y = (g**a)%p
print("g**a mod y%p is :", y)

x = (g**b)%p

print("g**b mod x%p is :", x)
ka = (y**a)%p
#print("y**a ka is :", ka)

print("y**a mod ka%p is :", ka)
kb = (x**b)%p

print("y**b mod kb%p is :", kb)

m1 = (x**a)%p
print("x**a mod m1%p is :", m1)
m2 = (y**b)%p

print("y**b mod m2%p is :", m2)
if m1 == m2:
    print("The value of m1 and m2 are equal")
    print("The secret key is: ", m1)