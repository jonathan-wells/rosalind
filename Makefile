CC = gcc
CFLAGS = -Wall -std=c99

bin/main: $(wildcard src/*.c)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

run: bin/main
	bin/main

clean:
	rm -f bin/main

.PHONY: run clean
