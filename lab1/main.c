#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>

#include "mylib/mylib.h"

#define WORD_SIZE 30

struct timespec begin, end;
struct timespec cpu_begin, cpu_end;

int main() {
    double all_time = 0;
    double all_time_cpu = 0;

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
            init(n);
        }
        else if(strcmp(s1,"remove_block") == 0){
            int i;
            scanf("%d",&i);
            remove_block(i);
        }
        else if(strcmp(s1,"remove_row") == 0){
            int i,ii;
            scanf("%d %d",&i,&ii);
            remove_row(i,ii);
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
                int i = merge_files(s1,s2);
                printf("index %d",i);
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
    clean();
    printf("cpu Time measured: %.3f seconds.\n", all_time_cpu);
    printf("wall time measured: %.3f seconds.\n", all_time);
    return 0;
    /*Testing:

     */
}
