#include <stdio.h>
#include <math.h>
int main() {
    FILE *fp,*fp_a, *fp_b, *fp_c;
    fp = fopen("dane.txt","r");
    fp_a = fopen("a.txt","w");
    fp_b = fopen("b.txt","w");
    fp_c = fopen("c.txt","w");

    int evenCounter = 0;

    int n;
    while (fscanf(fp,"%d\n",&n) != EOF){
        if(n%2 == 0)
            evenCounter++;

        if(n >10){
            int b = (n/10)%10;
            if(b == 0 || b == 7){
                fprintf(fp_b,"%d\n",n);
            }
        }
        if((int)sqrt(n) * (int)sqrt(n) == n)
            fprintf(fp_c,"%d\n",n);
    }
    fprintf(fp_a,"Liczb parzystych jest %d",evenCounter);
    fclose(fp);
    fclose(fp_a);
    fclose(fp_b);
    fclose(fp_c);
    return 0;
}
