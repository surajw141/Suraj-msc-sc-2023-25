CC = g++
CFLAGS = -std=c++11

all: main

main: main.cpp Board.cpp Queen.cpp Board.h Queen.h
	$(CC) $(CFLAGS) -o main main.cpp Board.cpp Queen.cpp

clean:
	rm -rf main