#include<stdio.h>

int main(void)
{
    int j= 0;
    printf("Numbers: ");
    for(int i=1; i<1000; i++)
    {
        if ((i%3) == 0 || (i%5) == 0)
        {
            printf("%i, ", i);
            j += i;
        }
    }
    printf("\n");
    printf("Sum is: %i\n", j);
}