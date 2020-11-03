/*
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

#include<stdio.h>

int main (void)
{
    long chain = 0;
    long number = 2;
    long copy;
    long maxChain = 0;
    long maxNumber = 0;
    long limit;

    printf("What's the uplimit: ");
    scanf("%li", &limit);

    for(int i = 0; i<limit; i++)
    {
        copy = number;
        while(number > 1)
        {
            if((number%2) == 0)
            {
                number = number/2;
                chain++;
            }
            else
            {
                number = 3*number + 1;
                chain++;
            }
        }
        if(chain > maxChain)
        {
            maxChain = chain;
            maxNumber = copy;
        }
        chain = 0;
        number = copy + 1;
    }

    printf("Under %li, the longest chain produced by: %li\n", limit, maxNumber);
    printf("Max chain is: %li\n", maxChain);
}