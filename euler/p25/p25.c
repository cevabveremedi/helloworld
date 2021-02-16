/*
    The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
    Hence the first 12 terms will be:

    F1 = 1
    F2 = 1
    F3 = 2
    F4 = 3
    F5 = 5
    F6 = 8
    F7 = 13
    F8 = 21
    F9 = 34
    F10 = 55
    F11 = 89
    F12 = 144
    The 12th term, F12, is the first term to contain three digits.

    What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
*/


#include <stdio.h>
#include <stdlib.h>

int* sumTwoArray(int* curr, int* prev);

int main(void)
{
    int current[1000] = {0};
    int* prev = malloc(sizeof(int)*1000);

    current[0] = prev[0] = 1;
    long long index = 2;
    
    while(current[999] == 0)
    {
        prev = sumTwoArray(current, prev);
        index++;
    }
    
    printf("index: %d\n", index);
    
    free(prev);
}

int* sumTwoArray(int* curr, int* prev)
{
    int carry = 0;
    int* nextPrev = malloc(sizeof(int)*1000);

    for(int i = 0; i < 1000; i++)
    {
        nextPrev[i] = curr[i];

        int total = curr[i] + prev[i] + carry;
        carry = total / 10;
        curr[i] = total % 10;
    }

    free(prev);
    return nextPrev;
}