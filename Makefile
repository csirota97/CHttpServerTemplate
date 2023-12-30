all: main

run: main
	./src/main.o 80

clean:
	rm src/*.o

main: src/main.c
	gcc src/main.c -o src/main.o -std=c11
