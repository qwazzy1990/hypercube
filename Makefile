CC = gcc
CFLAGS = -Wall -std=c11 -g -pedantic

program: makeprogram runprogram

makeprogram:
	$(CC) $(CFLAGS) -Iinclude -lm src/utilities.c src/HashMap.c src/DynamicString.c src/hypercube1.0.c src/StringBitPosition.c src/LinkedList.c test/main.c -o bin/prog1

runprogram:
	./bin/prog1

maketest: 
	$(CC) $(CFLAGS) -Iinclude -lm src/utilities.c src/HashMap.c src/DynamicString.c src/hypercube1.0.c src/StringBitPosition.c src/LinkedList.c test/testmain.c -o bin/test

valgrind: maketest mem-err mem-leak

mem-err: maketest
	valgrind ./bin/test

mem-leak: maketest
	valgrind --leak-check=full --show-leak-kinds=all ./bin/test

clean:
	rm ./bin/prog1
