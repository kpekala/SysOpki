#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>
#include <dlfcn.h>
#define WORD_SIZE 30

struct timespec begin, end;
struct timespec cpu_begin, cpu_end;

typedef void* (*arbitrary)();

void *handle = NULL;
void (*clean)();

void clean_data(){
    struct timespec c_begin, c_end;
    struct timespec c_cpu_begin, c_cpu_end;
    clock_gettime(CLOCK_REALTIME, &c_begin);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &c_cpu_begin);
    (void) clean();
    clock_gettime(CLOCK_REALTIME, &c_end);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &c_cpu_end);
    double w_t = (c_end.tv_sec - c_begin.tv_sec) + (c_end.tv_nsec - c_begin.tv_nsec)*1e-9;
    double cpu_t = (c_cpu_end.tv_sec - c_cpu_begin.tv_sec) + (c_cpu_end.tv_nsec - c_cpu_begin.tv_nsec)*1e-9;
    printf("cleaning cpu Time measured: %.3f seconds.\n", cpu_t);
    printf("cleaning wall time measured: %.3f seconds.\n", w_t);
}

int main() {
    double all_time = 0;
    double all_time_cpu = 0;

    void *handle = dlopen("mylib/mylib.so", RTLD_LAZY);
    if(!handle){printf("error\n");}
    void (*fun_init)() = (void (*)())dlsym(handle,"init");
    void (*remove_block)() = (void (*)())dlsym(handle,"remove_block");
    void (*remove_row)() = (void (*)())dlsym(handle,"remove_row");
    void (*merge_files)() = (void (*)())dlsym(handle,"merge_files");
    clean= (void (*)())dlsym(handle,"clean");

    while (1){
        char s1[WORD_SIZE];
        scanf("%s",s1);
        clock_gettime(CLOCK_REALTIME, &begin);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_begin);
        if(strcmp(s1,"q") == 0)
            break;
        else if (strcmp(s1,"create_table") == 0){
            int n;
            scanf("%d",&n);
            (void) fun_init(n);
        }
        else if(strcmp(s1,"remove_block") == 0){
            int i;
            scanf("%d",&i);
            (void) remove_block(i);
        }
        else if(strcmp(s1,"remove_row") == 0){
            int i,ii;
            scanf("%d %d",&i,&ii);
            (void) remove_row(i,ii);
        }
        else if(strcmp(s1,"merge_files") == 0){
            char separator,check;
            scanf("%c", &separator);
            while (1){
                char s1[WORD_SIZE];
                char s2[WORD_SIZE];
                scanf("%[^:]",s1);
                scanf("%c",&separator);
                scanf("%s",s2);
                scanf("%c",&check);
                merge_files(s1,s2);
                //printf("index %d",i);
                //print_block(i);
                if (check == '\n')
                    break;
            }

        }
        clock_gettime(CLOCK_REALTIME, &end);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        long cpu_sec = cpu_end.tv_sec - cpu_begin.tv_sec;
        long cpu_nansec = cpu_end.tv_nsec - cpu_begin.tv_nsec;
        all_time += seconds + nanoseconds*1e-9;
        all_time_cpu += cpu_sec + cpu_nansec*1e-9;
    }

    clean_data();
    printf("cpu Time measured: %.3f seconds.\n", all_time_cpu);
    printf("wall time measured: %.3f seconds.\n", all_time);
    dlclose(handle);
    return 0;
    /*Testing:

     */
}
