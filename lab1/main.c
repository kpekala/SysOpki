#include <stdio.h>
#include <stdlib.h>

#include "mylib/mylib.h"

#define WORD_SIZE 30;

int main() {
    /*char f_name1[20] = "file1.txt";
    char f_name2[20] = "file2.txt";
    init(5);
    merge_files(f_name1,f_name2);
    merge_files(f_name1,f_name2);
    printf("Size of merged block: %d\n",rows_number(0));
    printf("Size of merged block: %d\n",rows_number(1));
    remove_row(0,1);
    printf("fei: %d\n",first_empty_index());
    print_block(0);
    remove_block(1);
    printf("fei: %d\n",first_empty_index());
    clean();*/


    while (1){
        char s1[40];
        scanf("%s",s1);
        if(strcmp(s1,"q") == 0)
            break;
        else if (strcmp(s1,"create_table") == 0){
            int n;
            scanf("%d",&n);
            init(n);
        }
        else if(strcmp(s1,"remove_block") == 0)){
            int i;
            scanf("%d",&i);
            remove_block(i);
        }
        else if(strcmp(s1,"remove_row") == 0)){
            int i,ii;
            scanf("%d %d",&i,&ii);
            remove_row(i,ii);
        }
        else if(strcmp(s1,"merge_files") == 0)){
            int i,ii;
            scanf("%d %d",&i,&ii);
            remove_row(i,ii);
        }

    }
    clean();
    return 0;
}
