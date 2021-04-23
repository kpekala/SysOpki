all: build

build: server.o client.o
	gcc server.o -o server
	gcc client.o -o client

client.o:
	gcc -c client.c -g -ggdb3
server.o:
	gcc -c server.c -g -ggdb3

clean:
	rm -f client.o
	rm -f server.o
	rm -f client
	rm -f server

vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main