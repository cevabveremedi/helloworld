//Creates a triangle of size n, with numbers in it.

#include <stdio.h> 
  
int main (void)
{
    int n = 0;

    printf("Size of the triangle must be odd, greater than 1 and less than 19\n");
    while(n<=2 || n>=19 || (n%2) == 0)
    {
        printf("Size: ");
        scanf("%d", &n);
    }
    printf("\n");
    
    int line = 1;
    int mid = (n + 1)/2;

    for(int i = 0; i<n; i=i+2)
    {
        int num = 1;
        for(int j = 0; j<mid-line; j++)
        {
            printf(" ");
        }
        printf("/");
        for(int j = 0; j<line; j++)
        {
            printf("%d", num);
            num++;
        }
        num--;
        for(int j = 0; j<line-1; j++)
        {
            num--;
            printf("%d", num);
        }
        printf("\\");
        printf("\n");
        line++;
    }
    printf("\n");
}