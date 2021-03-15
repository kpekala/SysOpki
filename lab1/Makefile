all: build

build: main.o
	gcc main.o mylib/mylib.a -o main

shared: main.o
	gcc -L/home/konrad/Pulpit/Studia/sysopy/laby/lab1/mylib -Wall -ggdb3 -o main main.c -l:mylib.so
	export LD_LIBRARY_PATH=/home/konrad/Pulpit/Studia/sysopy/laby/lab1/mylib:$LD_LIBRARY_PATH
main.o: main.c
	gcc -c main.c -g -ggdb3

clean:
	rm -f main.o
	rm -f mylib.o
	rm -f main

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main

test:
	./main
	create_table 5