CC=g++
CFLAGS=-Wall -ansi -pedantic.
game:main.c
	$(CC) $(CFLAGS) main.c -o game
