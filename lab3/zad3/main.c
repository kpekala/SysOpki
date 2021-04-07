#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define PATH_SIZE 60
#define MAX_FILE_SIZE 256

int is_directory(const char *path);
int is_text_file(const char *path);
void search_directory(const char dir_path[PATH_SIZE], char* pattern, int depth_left, pid_t pid);
int is_real_directory(const char *path);
int pattern_in_file(char * f_path,char * pattern);

int base_path_size = -1;

int main(int argc, char *argv[]) {
    // Na wejsciu dostajemy: 1. sciezke, 2. lancuch, 3. maksymalna dlugosc
    if(argc != 4){
        printf("Number of arguments needs to be exactly 3\n");
        return 1;
    }
    char* path = argv[1];
    char* pattern = argv[2];
    int max_depth = atoi(argv[3]);
    base_path_size = strlen(path);
    search_directory(path, pattern, max_depth, getpid());

    return 0;
}

void search_directory(const char dir_path[PATH_SIZE], char* pattern, int depth_left, pid_t pid){
    DIR* dir = opendir(dir_path);
    if (dir == NULL){
        printf("Dir is null, %s\n",dir_path);
        return;
    }

    struct dirent* file_d = readdir(dir);
    while (file_d != NULL){
        //printf("%s: %s\n",dir_path, file_d->d_name);
        char f_path[PATH_SIZE] = "";
        strcat(f_path,dir_path);
        strcat(f_path,file_d->d_name);
        if(is_directory(f_path) && is_real_directory(f_path) && depth_left > 0){
            //bez nowego procesu narazie
            pid_t child_pid = fork();
            if(child_pid == 0){
                //printf("Going to %s\n",f_path);
                strcat(f_path,"/");
                search_directory(f_path, pattern, depth_left-1, getpid());
                closedir(dir);
                return;
            }
        }else if(is_text_file(f_path) && pattern_in_file(f_path, pattern)){
            printf("Relative path: %s\n",&f_path[base_path_size]);
            printf("Pattern in %s found by process: %d\n",f_path, pid);
        }
        file_d = readdir(dir);
    }

    closedir(dir);
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

int is_real_directory(const char *path){
    return strstr(path,"..") == NULL && path[strlen(path)-1] != '.';
}

int pattern_in_file(char * f_path, char * pattern){
    FILE * fp1;
    fp1 = fopen(f_path, "r");
    if (fp1 == NULL){
        printf("Cannot read file\n");
        return 0;
    }
    char * buffer1 = calloc(MAX_FILE_SIZE, sizeof(char));
    fread(buffer1, sizeof(char), MAX_FILE_SIZE,fp1);
    char* result = strstr(buffer1, pattern);
    free(buffer1);
    fclose(fp1);
    return result != NULL;
}