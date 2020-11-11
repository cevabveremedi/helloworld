/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, 
we can see that the 6th prime is 13.

What is the 10,001st prime number?
*/

#include<stdio.h>

int main (void)
{
    long prime_count = 1;
    long number = 3;

    while (prime_count<10001)
    {   
        int j = number+1;
        for(long i = 2; i<number; i++)
        {
            if((number%i) == 0)
            {
                j = i;
                break;
            }
        }
        if((number%j) == 0)
        {
            number++;
            continue;
        }
        number++;
        prime_count++;
    }
    printf("last prime so far: %li\n", number-1);
}