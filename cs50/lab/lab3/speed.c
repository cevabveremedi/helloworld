#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(void)
{
    char* array[9] = {"random5000.txt", "reversed10000.txt", "reversed50000.txt", "sorted10000.txt", "sorted50000.txt", "random10000.txt", "random50000.txt", "reversed5000.txt", "sorted5000.txt"};
    char buffer[50];

    clock_t tic1 = clock();
    for(int i = 0; i < 9; i++)
    {
        sprintf(buffer, "./sort1 %s", array[i]);
        system(buffer);
    }
    clock_t toc1 = clock();

    clock_t tic2 = clock();
    for(int i = 0; i < 9; i++)
    {
        sprintf(buffer, "./sort2 %s", array[i]);
        system(buffer);
    }
    clock_t toc2 = clock();

    clock_t tic3 = clock();
    for(int i = 0; i < 9; i++)
    {
        sprintf(buffer, "./sort3 %s", array[i]);
        system(buffer);
    }
    clock_t toc3 = clock();

    printf("Elapsed: %f seconds for sort 1\n", (double)(toc1 - tic1) / CLOCKS_PER_SEC);
    printf("Elapsed: %f seconds for sort 2\n", (double)(toc2 - tic2) / CLOCKS_PER_SEC);
    printf("Elapsed: %f seconds for sort 3\n", (double)(toc3 - tic3) / CLOCKS_PER_SEC);
}