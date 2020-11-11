/*
Starting in the top left corner of a 2×2 grid, and only being able to 
move to the right and down, 

there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
*/

#include<stdio.h>

int main(void)
{
    unsigned long long grid[21][21] = {[0 ... 20][0 ... 20] = 1};

    for(int i = 1; i<21; i++)
    {
        for(int j = 1; j<21; j++)
        {
            grid[i][j] = grid[i-1][j] + grid[i][j-1];
        }
    }

    printf("Result: %lld\n", grid[20][20]);
}