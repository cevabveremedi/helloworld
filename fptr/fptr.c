/**
 * this little program tests the function pointers
 * by using bubble sort algorithm w/ using an array an
 * increasing & decreasing order functions as parameter.
*/

#include<stdio.h>
#include<stdlib.h>

void bubbleSort(int* array, int len, int (*fptr)(int, int));
int increasingOrder(int a, int b);
int decreasingOrder(int a, int b);
void displayArray(int* array, int len);

int main(void)
{
    int array[] = {5,6,3,2,1,7,10,15,100,43,65,97,43};
    int len = sizeof(array)/sizeof(array[0]);

    printf("normal:\t\t");
    displayArray(array, len);

    printf("increasing:\t");
    bubbleSort(array, len, increasingOrder);
    displayArray(array, len);

    printf("decreasing:\t");
    bubbleSort(array, len, decreasingOrder);
    displayArray(array, len);
}

void bubbleSort(int* array, int len, int (*fptr) (int, int))
{
    for(int i = 0; i<len; i++)
    {
        for(int i = 0; i<len-1; i++)
        {
            if(fptr(array[i], array[i+1]))
            {
                array[i] = array[i] + array[i+1];
                array[i+1] = array[i] - array[i+1];
                array[i] = array[i] - array[i+1];
            }
        }
    }
}

int increasingOrder(int a, int b)
{
    return (a > b) ? 1 : 0;
}

int decreasingOrder(int a, int b)
{
    return (a < b) ? 1 : 0;
}

void displayArray(int* array, int len)
{
    for(int i = 0; i<len; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
}