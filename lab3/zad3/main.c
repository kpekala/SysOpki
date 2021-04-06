#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int is_directory(const char *path);
int is_text_file(const char *path);

int main(int argc, char *argv[]) {
    // Na wejsciu dostajemy: 1. sciezke, 2. lancuch, 3. maksymalna dlugosc
    if(argc != 4){
        printf("Number of arguments needs to be exactly 3\n");
        return 1;
    }
    char* path = argv[1];
    char* pattern = argv[2];
    int max_depth = atoi(argv[3]);

    DIR* dir = opendir(path);
    if (dir == NULL){
        printf("Dir is null\n");
        return 1;
    }

    struct dirent* file_d = readdir(dir);
    while (file_d != NULL){
        printf("Kolejny pliczek: %s\n",file_d->d_name);
        char f_path[50] = "";
        strcat(f_path,path);
        strcat(f_path,file_d->d_name);
        printf("Sciezka pliczku: %s\n",f_path);
        printf("Fajny katalog? %d\n",is_directory(f_path));
        file_d = readdir(dir);
    }

    closedir(dir);
    return 0;
}

int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

int is_text_file(const char *path){
    return strstr(path,".txt") != NULL;
}

