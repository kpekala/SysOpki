#include <stdio.h>
#include <stdlib.h>

#include "mylib/mylib.h"

#define WORD_SIZE 30

int main() {
    while (1){
        char s1[WORD_SIZE];
        scanf("%s",s1);
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
                print_block(i);
                if (check == '\n')
                    break;
            }

        }

    }
    clean();
    return 0;

    /*Testing:
    create_table 5
    merge_files file1.txt:file2.txt file1.txt:file2.txt
     */
}
