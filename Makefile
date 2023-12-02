C = gcc
CFLAGS = -Wall
build:
	$(C) $(CFLAGS) main.c -o main -lSDL2 -lSDL2_ttf

run:
	./main

clean:
	rm main