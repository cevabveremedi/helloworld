#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(void)
{
    FILE* names = fopen("data.txt", "r");
    int namenum = 0;
    int chnum = 0;
    char namearray[5163][30];

    for(char c = fgetc(names); c != EOF; c = fgetc(names))
    {
        if(c > 64 && c < 91)
        {
            namearray[namenum][chnum++] = c;
        }
        else if(c == 44)
        {
            namearray[namenum][chnum] = '\0';
            namenum++;
            chnum = 0;
        }
    }
    fclose(names);
    qsort(namearray, 5163, 30, strcmp);

    long long totalSum = 0;

    for(int i = 0; i<5163; i++)
    {
        long long sum = 0;
        for(int j = 0; namearray[i][j] != '\0'; j++)
        {
            sum += namearray[i][j] - 'A' + 1;
        }
        sum *= (i+1);
        totalSum += sum;
    }
    printf("total sum: %lld\n", totalSum);
}
