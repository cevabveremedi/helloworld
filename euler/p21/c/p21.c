/*
# Let d(n) be defined as the sum of proper divisors of n 
# (numbers less than n which divide evenly into n).

# If d(a) = b and d(b) = a, where a ≠ b, 
# then a and b are an amicable pair and each of a and b are called amicable numbers.

# For example, the proper divisors of 
# 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. 
# The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

# Evaluate the sum of all the amicable numbers under 10000.
*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int sumDivisors(int n)
{
    int total = 0;
    for(int i = 1; i<=n/2; i++)
    {
        if(n % i == 0)
        {
            total += i;
        }
    }
    return total;
}

int main(void)
{
    int sum = 0;
    printf("amicable numbers below 10000 are:\n");
    for(int i = 1; i<10000; i++)
    {
        int sumDiv = sumDivisors(i);
        if(sumDiv == i) continue;
        if(sumDivisors(sumDiv) == i)
        {
            sum += i;
            printf("[%d]\n", i);
        }
    }
    printf("sum of all the amicable numbers in range:\t%d\n", sum);
}