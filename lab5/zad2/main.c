#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>

#define MAX_LINE_SIZE 256

int main(int argc, char *argv[]) {
    char buffer1[MAX_LINE_SIZE];
    FILE *date = popen("date", "r");
    fgets(buffer1, MAX_LINE_SIZE, date);
    printf("date command data: %s", buffer1);
    fclose(date);
}