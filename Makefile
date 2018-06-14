CC = gcc
CFLAGS = -Wall -std=c11 -g -pedantic

prog1:

	$(CC) $(CFLAGS) -Iinclude -lm src/utilities.c src/HashMap.c src/DynamicString.c src/hypercube1.0.c test/testmain.c -o bin/prog1

clean:
	rm bin/prog1
