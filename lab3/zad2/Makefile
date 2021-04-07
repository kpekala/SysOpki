all: build

build: main.o
	gcc main.o mylib/mylib.a -o main

main_dynamic.o:
	gcc -c main_dynamic.c -g -ggdb3

main.o: main.c
	gcc -c main.c -g -ggdb3

clean:
	rm -f main.o
	rm -f mylib.o
	rm -f main_dynamic.o
	rm -f main

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no --leak-check=full --show-leak-kinds=all ./main


