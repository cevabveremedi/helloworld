//makes a diamond size of n with using '+' and '*'

#include <stdio.h> 
  
int main (void)
{
    int n;
    do
    {
        printf("Enter a positive odd number: ");
        scanf("%d", &n);
    }while(n<2 || (n%2 == 0));

    int decrease = 1;

    int stars = (n-1)/2;
    int plus = 1;

    printf("\n");

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<stars; j++)
        {
            printf("*");
        }
        for(int j = 0; j<plus; j++)
        {
            printf("+");
        }
        for(int j = 0; j<stars; j++)
        {
            printf("*");
        }
        printf("\n");

        if(stars == 0)
        {
            decrease = 0;
        }

        if(decrease == 1)
        {
            stars--;
            plus = plus + 2;
        }
        else
        {
            stars++;
            plus = plus - 2;
        }
    }
    printf("\n");
}