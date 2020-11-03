/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

#include<stdio.h>

int main(void)
{
    int a, b, c, sum;

    printf("Define the size of a+b+c =  ");
    scanf("%i", &sum);
    int found = 0;

    for(a = sum/3; a < sum/2; a++) //a is the middle number, it must be smaller than sum/2.
    {
        for(b = 1; b <= sum/3; b++) //b is the smallest number.
        {
            c = sum - a - b;
            if(a*a + b*b == c*c)
            {
                printf("a: %i, b: %i, c: %i\n", a, b, c);
                long product = a*b*c;
                printf("product: %li\n", product);
                found = 1;
            }
        }
    }
    if(found == 0)
    {
        printf("Invalid number!\n");
    }
}