CC = gcc
CFLAGS = -Wall -std=c99

all: bin/main

bin/main: obj/main.o obj/dna.o
	$(CC) obj/main.o obj/dna.o -o bin/main

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/dna.o: src/dna.c src/dna.h
	$(CC) $(CFLAGS) -c src/dna.c -o obj/dna.o

run: all
	bin/main

clean:
	rm -f obj/*.o bin/main
