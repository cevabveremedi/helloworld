/*If the numbers 1 to 5 are written out in words: 
one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, 
how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 
23 letters and 115 (one hundred and fifteen) contains 20 letters. 
The use of "and" when writing out numbers is in compliance with British usage.*/

#include<stdio.h>

int digits (int x);
int tensDigit(int x);
int hundredsDigit(int x);

int main(void)
{
    long total = 0;
    
    for(int i = 1; i <= 1000; i++)
    {
        if(i < 10)
        {
            total += digits(i);
        }
        else if(i<100)
        {
            total += tensDigit(i);
        }
        else if(i<1000)
        {
            total += hundredsDigit(i);
        }
        else
        {
            total += 11;
        }
    }

    printf("Total: %ld\n", total);
}

int digits (int x)
{
    switch (x)
    {
        case 1:
            return 3;
        case 2:
            return 3;
        case 3:
            return 5;
        case 4:
            return 4;
        case 5:
            return 4;
        case 6:
            return 3;
        case 7:
            return 5;
        case 8:
            return 5;
        case 9:
            return 4;
        case 0:
            return 0;
    }
    return 0;
}

int tensDigit(int x)
{
    if(x < 10)
    {
        return digits(x);
    }

    if(10 <= x && x<20)
    {
        switch (x)
        {
            case 10:
                return 3;
            case 11:
                return 6;
            case 12:
                return 6;
            case 13:
                return 8;
            case 14:
                return 8;
            case 15:
                return 7;
            case 16:
                return 7;
            case 17:
                return 9;
            case 18:
                return 8;
            case 19:
                return 8;
        }
    }
    else if(20 <= x && x < 30)
    {
        return 6 + (digits(x%10));
    }
    else if(30 <= x && x < 40)
    {
        return 6 + (digits(x%10));
    }
    else if(40 <= x && x < 50)
    {
        return 5 + (digits(x%10));
    }
    else if(50 <= x && x < 60)
    {
        return 5 + (digits(x%10));
    }
    else if(60 <= x && x < 70)
    {
        return 5 + (digits(x%10));
    }
    else if(70 <= x && x < 80)
    {
        return 7 + (digits(x%10));
    }
    else if(80 <= x && x < 90)
    {
        return 6 + (digits(x%10));
    }
    else if(90 <= x && x < 100)
    {
        return 6 + (digits(x%10));
    }
    return 0;
}

int hundredsDigit(int x)
{
    if(100 <= x && x < 200)
    {
        if(x == 100)
        {
            return 10;
        }
        else
        {
            return 13 + (tensDigit(x%100));
        }
    }
    else if(200 <= x && x < 300)
    {
        if(x == 200)
        {
            return 10;
        }
        else
        {
            return 13 + (tensDigit(x%100));
        }
    }
    else if(300 <= x && x < 400)
    {
        if(x == 300)
        {
            return 12;
        }
        else
        {
            return 15 + (tensDigit(x%100));
        }
    }
    else if(400 <= x && x < 500)
    {
        if(x == 400)
        {
            return 11;
        }
        else
        {
            return 14 + (tensDigit(x%100));
        }
    }
    else if(500 <= x && x < 600)
    {
        if(x == 500)
        {
            return 11;
        }
        else
        {
            return 14 + (tensDigit(x%100));
        }
    }
    else if(600 <= x && x < 700)
    {
        if(x == 600)
        {
            return 10;
        }
        else
        {
            return 13 + (tensDigit(x%100));
        }
    }
    else if(700 <= x && x < 800)
    {
        if(x == 700)
        {
            return 12;
        }
       else
        {
           return 15 + (tensDigit(x%100));
        }
    }
    else if(800 <= x && x < 900)
    {
       if(x == 800)
        {
            return 12;
        }
        else
        {
            return 15 + (tensDigit(x%100));
        }
    }
    else if(900 <= x && x < 1000)
    {
        if(x == 900)
        {
            return 11;
        }
        else
        {
            return 14 + (tensDigit(x%100));
        }
    }
    return 0;
}