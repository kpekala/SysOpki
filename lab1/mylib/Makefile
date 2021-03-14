all: static

static:
	gcc -c mylib.c
	ar rcs mylib.a mylib.o

shared:
	gcc -c -Wall -Werror -fpic mylib.c
	gcc -shared -o mylib.so mylib.o
clean:
	rm -f mylib.o
	rm -f mylib.a
	rm -f mylib.so
