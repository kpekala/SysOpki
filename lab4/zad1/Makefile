all: build

build: fork_ver.o
	gcc fork_ver.o -o fork_ver

fork_ver.o: fork_ver.c
	gcc -c fork_ver.c -g -ggdb3

clean:
	rm -f fork_ver.o
	rm -f fork_ver
	rm -f exec_ver.o
	rm -f exec_ver

build_e: exec_ver.o
	gcc signal_test.c -o signal_test
	gcc exec_ver.o -o exec_ver

exec_ver.o: exec_ver.c
	gcc -c exec_ver.c -g -ggdb3


vlgr:
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./fork_ver
