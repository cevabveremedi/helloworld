/*
Starting in the top left corner of a 2×2 grid, and only being able to 
move to the right and down, 

there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
*/

#include<stdio.h>

double fact(int n, int k)
{
    return (n == k) ? n: n*fact(n-1, k);
}

int main(void)
{
    double i = fact(40, 21);
    double j = fact(20, 2);

    printf("Result: %.0f\n", i/j);
}