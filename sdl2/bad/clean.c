#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    int digit = 1;
    while(digit != 7)
    {
        char buffer[64];
        sprintf(buffer, "cd bad0%d; make clean; cd ..", digit);
        system(buffer);
        digit++;
    }
}