C = gcc
CFLAGS = -Wall
build:
	$(C) $(CFLAGS) main.c -o main -lSDL2

run:
	./main

clean:
	rm -rf *
