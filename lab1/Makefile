all: build

build: main.o mylib.o
	gcc main.o mylib.o -o main


mylib.o: mylib.c
	gcc -c mylib.c

main.o: main.c
	gcc -c main.c -g

clean:
	rm -f main.o
	rm -f mylib.o
	rm -f main

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main