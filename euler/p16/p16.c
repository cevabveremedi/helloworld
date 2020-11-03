/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

#include<stdio.h>
#include<math.h>

int main(void)
{
    /* 2^1000, in binary -> 1000 0000 ... 000 (1000 times 0)

    maybe
    1<<1000 */

    int numArray[2000] = {0};
    numArray[0] = 1;
    int carry = 0;
    int num;

    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            num = numArray[j]*2;
            numArray[j] = (num % 10) + carry;
            carry = num/10;
            num = 0;
        }
    }

    int total = 0;

    for(int i = 0; i<2000; i++)
    {
        total += numArray[i];
    }

    printf("Total:  %i\n", total);
}