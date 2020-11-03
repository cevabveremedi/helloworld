//2520 is the smallest number that can be divided by each of the numbers
//from 1 to 10 without any remainder.

//What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

#include<stdio.h>

int main(void)
{
    //1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20//
    //Find the least common multiple (LCM)//

    int nums[19] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; 
    int lcm = 1;
    int i;
    int size = sizeof(nums)/sizeof(nums[0]);
    printf("%i\n", size);
    
    for(i = 0; i<size; i++) // i < sizeof the array;
    {
        int div = 2;
        while(nums[i] > 1)
        {
            while((nums[i]%div)==0)
            {
                for(int j=1; j<size-i; j++) // j < sizeof the array - i;
                {
                    if((nums[i+j]%div)==0)
                    {
                        nums[i+j] = nums[i+j]/div;
                    }
                }
                nums[i] = nums[i]/div;
                lcm = lcm*div;
            }
            div++;
        }
    }
    printf("Least common multiple is: %i\n", lcm);
}