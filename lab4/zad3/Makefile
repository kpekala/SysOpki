all: build

build: sender.o catcher.o
	gcc sender.o -o sender
	gcc catcher.o -o catcher

nbuild: nsender.o ncatcher.o
	gcc nsender.o -o nsender
	gcc ncatcher.o -o ncatcher

catcher.o: catcher.c
	gcc -c catcher.c -g -ggdb3
sender.o: sender.c
	gcc -c sender.c -g -ggdb3

ncatcher.o: ncatcher.c
	gcc -c ncatcher.c -g -ggdb3
nsender.o: nsender.c
	gcc -c nsender.c -g -ggdb3

clean:
	rm -f sender.o
	rm -f nsender.o
	rm -f catcher.o
	rm -f ncatcher.o
	rm -f sender
	rm -f nsender
	rm -f catcher
	rm -f ncatcher

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main
