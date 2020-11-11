//A palindromic number reads the same both ways. 
//The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
//Find the largest palindrome made from the product of two 3-digit numbers.

#include<stdio.h>

int main(void)
{
    int maxNumber = 0;
    for(int i = 100; i<1000; i++)
    {
        for(int j = 100; j<1000; j++)
        {
            int number = i*j;
            int digits = number;
            int numberRev = 0;

            while(digits>0)
            {
                numberRev = numberRev * 10 + (digits%10);
                digits = digits/10;
            }

            if(numberRev == number)
            {
                if(number > maxNumber)
                {
                    maxNumber = number;
                }
            }
        }
    }
    printf("Biggest palindrome made from two-3 digit numbers: %i \n", maxNumber);
}