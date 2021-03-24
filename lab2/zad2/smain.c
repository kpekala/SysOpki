#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


#define MAX_LINE_SIZE 256

void do_magic(char symbol, char *f_name);

int main(int argc, char ** argv) {
    char* f_name;
    char symbol;
    if(argc < 3){
        printf("Error: not enough arguments passed\n");
        return 1;
    }
    symbol = *argv[1];
    f_name = argv[2];

    do_magic(symbol, f_name);
}

void do_magic(char symbol, char *f_name) {
    int fp1;
    fp1 = open(f_name,O_RDONLY);
    if (fp1 == -1){
        printf("Cannot read file\n");
        return;
    }
    char * line = calloc(MAX_LINE_SIZE, sizeof(char));
    while (1){
        char char_buffer;
        //reading line to buffer
        int hasSymbol = 0;
        size_t size1;
        for (int i = 0; i < MAX_LINE_SIZE; i++) {
            size1 = read(fp1,&char_buffer,1);
            if (size1 == 0 || char_buffer == '\n')
                break;
            line[i] = char_buffer;
            if (char_buffer == symbol)
                hasSymbol = 1;
        }
        if (hasSymbol)
            printf("%s\n",line);
        memset(line,0,strlen(line));
        if(size1 == 0)
            break;
    }
    free(line);
}

