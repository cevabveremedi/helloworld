//The prime factors of 13195 are 5, 7, 13 and 29.
//What is the largest prime factor of the number 600851475143 ?

#include<stdio.h>

int main(void)
{
    long number = 600851475143;
    long a = 2;
    int counter = 0;
    long temp_number, temp_a;

    while (number>1)
    {
        if((number%a) == 0)
        {
            temp_number = number;
            temp_a = a;
            if((temp_number%temp_a) == 0)
            {
                temp_number = temp_number/temp_a;
                counter++;
            }    
            if(!(temp_number%temp_a) == 0)
            {
                printf("%li^%i, ", temp_a, counter);
                counter = 0; 
            }
            number = number/a;
        }
        else
            a++;    
    }
    printf("\n");
}