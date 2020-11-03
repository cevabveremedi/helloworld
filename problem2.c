/**scans between 200-400. 
 * prints the number if it's all digits are even 
 * and counts the total.
 */

#include <stdio.h> 
  
int main (void)
{
    int total = 0;

    for(int i = 200; i <= 400; i++)
    {
        int copy = i;
        while((copy%2) == 0)
        {
            copy = copy/10;
            if(copy == 0)
            {
                printf("%d, ", i);
                total++;
                break;
            }
        }
    }

    printf("\nTotal: %d\n", total);
}