/*
    n! means n × (n − 1) × ... × 3 × 2 × 1

    For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
    and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

    Find the sum of the digits in the number 100!
*/

#include<stdio.h>

int main(void)
{
    int buffer[160] = {0};
    buffer[0] = 1;

    for(int i = 1; i<=100; i++)
    {
        int carry = 0;
        int rem = 0;
        for(int j = 0; j<160; j++)
        {
            int number = buffer[j]*i + carry;
            rem = number%10;
            carry = number/10;
            buffer[j] = rem;
        }
    }

    int total = 0;
    for(int i=0; i<160;i++)
    {
        total += buffer[i];
    }
    
    printf("\ntotal: %d\n", total);
}