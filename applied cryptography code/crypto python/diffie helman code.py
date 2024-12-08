#diffie hellman share secret key program

# there are four parameters p, g, x, h, a, b. that will be accpted from user

p = int(input("Enter the value of p: "))
g = int(input("Enter the value of g: "))
x = int(input("Enter the value of x: "))
h = int(input("Enter the value of h: "))
a = int(input("Enter the value of a: "))
b = int(input("Enter the value of b: "))
# calculate the value of y
y = (g**x)%p
# calculate the value of ka
ka = (h**a)%p
# calculate the value of kb
kb = (h**b)%p
# print the values of ka and kb
print("The value of ka is: ", ka)
print("The value of kb is: ", kb)
# check if ka and kb are equal
if ka == kb:
    print("The value of ka and kb are equal")
    print("The secret key is: ", ka)
    
else:
    print("The value of ka and kb are not equal")
    print("The secret key is: ", kb)
    print("The secret key is not equal to ka and kb")
    
