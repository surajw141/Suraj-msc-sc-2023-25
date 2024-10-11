CC = g++
CFLAGS = -Wall -std=c++11

all: main

main: main.o TriangleProp.o
	$(CC) $(CFLAGS) main.o TriangleProp.o -o main

main.o: main.cpp TriangleProp.h
	$(CC) $(CFLAGS) -c main.cpp

TriangleProp.o: TriangleProp.cpp TriangleProp.h
	$(CC) $(CFLAGS) -c TriangleProp.cpp

clean:
	rm -rf *.o main

