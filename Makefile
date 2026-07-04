CC = gcc
CFLAGS = -Wall -std=c99

all: bin/main

bin/main: build/main.o build/dna.o
	$(CC) build/main.o build/dna.o -o bin/main

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/dna.o: src/dna.c src/dna.h
	$(CC) $(CFLAGS) -c src/dna.c -o build/dna.o

run: all
	bin/main

clean:
	rm -f build/*.o bin/main
