#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    int digit1 = 0;
    int digit2 = 1;
    while(digit1 != 1 || digit2 != 6)
    {
        char buffer[64];
        sprintf(buffer, "cd shooter%d%d; make clean; cd..", digit1, digit2);
        system(buffer);
        digit2++;
        if(digit2 == 10)
        {
            digit1++;
            digit2 = 0;
        }
    }
}