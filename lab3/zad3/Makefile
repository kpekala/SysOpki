all: build

build: main.o
	gcc main.o -o main

main.o: main.c
	gcc -c main.c -g -ggdb3

clean:
	rm -f main.o
	rm -f main

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no --leak-check=full --show-leak-kinds=all ./main ./ siema 5

test:
	./main ./ siema 5

