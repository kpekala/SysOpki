
all: build

build: main.o structures.o parser.o
	gcc main.o structures.o parser.o -o main


structures.o:
	gcc -c structures.c -ggdb3
	ar rcs structures.a structures.o

parser.o:
	gcc -c parser.c -ggdb3
	ar rcs parser.a parser.o

main.o: main.c
	gcc -c main.c -g -ggdb3

clean:
	rm -f main.o
	rm -f main
	rm -f structures.o
	rm -f parser.o

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main