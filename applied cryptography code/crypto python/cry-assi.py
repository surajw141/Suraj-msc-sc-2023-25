# Demonstrate Diffie-Hellman key exchange for the following

# (a) Let p = 163, g = 2, a = 140, b =34

p = int(input("Enter the value of p: "))
g = int(input("Enter the value of g: "))
x = int(input("Enter the value of x: "))
h = int(input("Enter the value of h: "))
a = int(input("Enter the value of a: "))
b = int(input("Enter the value of b: "))
y = (g**x)%p
ka = (h**a)%p
kb = (h**b)%p
print("The value of ka is: ", ka)
print("The value of kb is: ", kb)
if ka == kb:
    print("The value of ka and kb are equal")
    print("The secret key is: ", ka)
    
else:
    print("The value of ka and kb are not equal")
    print("The secret key is: ", kb)
    print("Key exchange failed. Shared keys do not match.")