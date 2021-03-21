all: build

build: main.o
	gcc main.o -o main -lm

main.o: main.c
	gcc -c main.c -g -ggdb3

clean:
	rm -f main.o
	rm -f main

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main f1.txt  f2.txt
