/*
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. 
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/


#include<stdlib.h>
#include<stdio.h>

int factory(long long x);

int main(void)
{
    long long biggestNumber = 0;
    int max = 0;
    int number = 10;

    while(number < 10000000)
    {
        int chain = factory(number);
        if(chain > max)
        {
            max = chain;
            biggestNumber = number;
        }
        number++;
    }
    printf("The longest chain is %d\nProduced by %lld\n", max, biggestNumber);
}

int factory(long long x)
{
    int chain = 0;

    while(x > 1)
    {
        if((x % 2) == 0)
        {
            x /= 2;
        }
        else
        {
            x = 3*x + 1;
        }
        chain ++;
    }
    return chain;
}