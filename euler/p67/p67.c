/**
 * Same as problem 18 but harder.
 * There are 100 rows this time.
*/

#include<stdio.h>
#include<ctype.h>

int main(void)
{
    FILE* fp = fopen ("data.txt", "r");
    if(fp == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    int data[100][100];
    int number = 0;
    int row = 0;
    char ch, ch1;

    ch1 = fgetc (fp);
    while (ch1 != EOF)
    {
        ch = ch1;
        ch1 = fgetc (fp);

        if(isdigit(ch) && isdigit(ch1))
        {
            data[row][number] = 10*(ch -'0') + ch1 - '0';
        }
        else if(ch1 == '\n')
        {
            number = 0;
            row++;
        }
        else if(ch1 == ' ')
        {
            number++;
        }
    }
    fclose(fp);

    for(int i = 1; i<100; i++)
    {
        for(int j = 0; j<100; j++)
        {
            if(j == 0)
            {
                data[i][j] += data[i-1][j];
            }
            else if(j == i)
            {
                data[i][j] += data[i-1][j-1];               
            }
            else
            {
                int left = data[i-1][j-1];
                int right = data[i-1][j];

                if(left>right)
                {
                    data[i][j] += left;
                }
                else
                {
                    data[i][j] += right;
                }
            }
        }
    }

    int max = 0;

    for(int i = 0; i<100; i++)
    {
        if(data[99][i] > max)
        {
            max = data[99][i];
        }
    }
    
    printf("max: %d\n", max);
}