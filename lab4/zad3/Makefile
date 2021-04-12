all: build

build: sender.o catcher.o
	gcc sender.o -o sender
	gcc catcher.o -o catcher

catcher.o: catcher.c
	gcc -c catcher.c -g -ggdb3
sender.o: sender.c
	gcc -c sender.c -g -ggdb3

clean:
	rm -f sender.o
	rm -f catcher.o
	rm -f sender
	rm -f catcher

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main
