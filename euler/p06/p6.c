/*the difference between the sum of the squares of the first ten natural numbers 
and the square of the sum is: 3025 - 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers 
and the square of the sum.

(1 + 2 + 3... + 100)^2 = x
1^2 + 2^2 + 3^2... + 100^2 = y
x - y = ?
*/

#include<stdio.h>

int main (void)
{
    long sum_sq = 0;
    long sq_sum = 0;
    for(int i = 1; i<101; i++)
    {
        sum_sq += i;
        sq_sum += i*i;
    }
    sum_sq = sum_sq*sum_sq;

    long difference = sum_sq - sq_sum;
    printf("difference is: %li\n", difference);
}