CC = gcc
CFLAGS = -Wall -std=c11 -g -pedantic

prog1:
	mkdir bin
	$(CC) $(CFLAGS) -Iinclude -I..//utilities/include.. -I..//String/include ..//String/src/String.c src/hypercube.c test/testmain.c -o bin/prog1

clean:
	rm -r bin
