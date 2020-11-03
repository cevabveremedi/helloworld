/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

#include<stdio.h>
#include<math.h>

int main (void)
{
    long long x;
    printf("Find the sum of all primes below: ");
    scanf("%lli", &x);

    if(x > 10000000-1)
    {
        printf("Number is too big: %lli!\nTry something else!\n", x);
        return 1;
    }

    static int primes[10000000];
    long long i, j;
    long long sum = 0;

    for(i=0; i < x; i++)
    {
        primes[i] = 1;
    }

    for(i=2; i <= sqrt(x); i++)
    {
        for(j=i; j*i <= x; j++)
        {
            primes[i*j] = 0;
        }
    }
    for(i=2; i<=x; i++)
    {
        if(primes[i] == 1)
        {
            sum += i;
        }
    }
    printf("Sum of the primes below %lli: %lli\n", x, sum);
}

/* I've tried this code first. It works fine but it's too slow. So, I had to improve it...

#include<stdio.h>

int main(void)
{
    long prime = 0;
    long number = 2;
    int notPrime = 0;
    long x;
    printf("Find the sum of all primes below: ");
    scanf("%li", &x);

    while (number < x)
    {
        notPrime = 0;
        for(long i = 2; i<number; i++)
        {
            if((number%i)==0)
            {
                notPrime = 1;
                number++;
                break;
            }
        }
        if(notPrime == 1)
        {
            continue;
        }
        prime += number;
        number++;
    }
    printf("Sum of the primes below %li: %li\n", x, prime);
}

*/