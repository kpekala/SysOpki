all: build

build: main.o
	gcc main.o -o main

main.o: main.c
	gcc -c main.c -g -ggdb3

clean:
	rm -f main.o
	rm -f main
	rm -f smain
	rm -f smain.o

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main f1.txt  f2.txt
