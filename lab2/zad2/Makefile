all: build

build: main.o
	gcc main.o -o main

sbuild: smain.o
	gcc smain.o -o smain

main.o: main.c
	gcc -c main.c -g -ggdb3

smain.o: smain.c
	gcc -c smain.c -g -ggdb3

clean:
	rm -f main.o
	rm -f main

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main 5 f1.txt

svlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./smain p smain.c
