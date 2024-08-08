# file open

s = open('demo.txt',mode= 'r')
print(s.read())
s.close()


# file open

with open('demo.txt',mode= 'w') as file:
    file.write('hello world')
    
    
with open('demo.txt',mode= 'a') as file:
    file.write('Appending this text')
    file.close()
    
    
with open('example.bin',mode= 'rb') as file:
    file.write('Appending this text')
    file.close()