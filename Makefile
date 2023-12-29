# all: main httpNetworking
all: main

# run: main httpNetworking
run: main
	./src/main.o 80

clean:
	rm src/*.o

main: src/main.c
	gcc  src/main.c -o src/main.o

# httpNetworking: src/httpNetworking.c
# 	gcc src/httpNetworking.c -o src/httpNetworking.o