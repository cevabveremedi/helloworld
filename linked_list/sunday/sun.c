/*
You are given the following information, but you may prefer to do some research for yourself.

    -1 Jan 1900 was a Monday.
    -Thirty days has September, April, June and November.
        All the rest have thirty-one,
        Saving February alone,
        Which has twenty-eight, rain or shine.
        And on leap years, twenty-nine.
    -A leap year occurs on any year evenly divisible by 4, 
        but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century 
(1 Jan 1901 to 31 Dec 2000)?
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct month
{
    int monthNum;
    int howManyDay;
    struct month *nextMonth;
}month;

typedef struct day
{
    int dayNum;
    struct day *nextDay;
}day;

month *firstMonth = NULL;
day *firstDay = NULL;

/*
    creates a circular linked list of months
    and circular linked list of days.
*/
void createMonth(int data);
void daysofMonth(void);
void createDay(int data);
void clearMemory(void);

int main(void)
{
    int arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for(int i = 0; i<12; i++)
    {
        createMonth(arr[i]); //sets the months
    }

    daysofMonth(); //sets the days of months

    int arr2[7] = {1, 2, 3, 4, 5, 6, 7};
    for(int i= 0; i<7; i++)
    {
        createDay(arr2[i]); //sets the days of the week
    }

    month *february = firstMonth->nextMonth; //points feb
    month *currentMonth = firstMonth; //starts from the jan
    day *currentDay = firstDay->nextDay->nextDay; 
    /*
        Note: I checked the date 1 jan 1901 in google, 
        it said it's tuesday. But when I init currentDay
        to tuesday, the souliton was wrong (172).
        So I calculate by myself based on the given info
        ("1 Jan 1900 was a Monday"), 1900 was a leap year
        so there were 366 days. 366 % 7 = 2
        So 1 jan 1901 is monday-> tuesday-> wednesday.
        I've init the currentDay to '3' this time and 
        the solution was true (171)!
    */

    //scan 1 jan 1901 to 31 dec 2000
    int day = 1;
    int year = 1901;
    int total = 0;

    while(1)
    {
        /*
            if it's the last month of the year 
            and the last day of the month,
            increases the year.
        */
        if(((currentMonth->monthNum) % 12 ) == 0)
        {
            if(day == (currentMonth->howManyDay))
            {
                year++;
                
                if(year == 2001)
                {
                    printf("Completed!\n");
                    break;
                }
            }
        }

        /*
            if it's the last day of the month,
            increases the month.
        */
        if(day == (currentMonth->howManyDay))
        {
            day = 0;
            currentMonth = currentMonth->nextMonth;
            
            //if it's sunday, increases the total count.
            if(((currentDay->dayNum) % 7) == 0)
            {
                total++;
            }
        }
        
        //checks the leap year conditions.
        if(((year % 4) == 0 ) || ((year % 100 == 0) && (year % 400 == 0)))
        {
            february->howManyDay = 29;
        }
        else
        {
            february->howManyDay = 28;
        }

        //increases the day value at the end of each loop.
        day++;
        currentDay = currentDay->nextDay;
    }

    printf("Total: %d\n", total);

    clearMemory(); //frees allocated memory
}

void createMonth(int data)
{
    month *temp = (month *) malloc(sizeof(month));
    temp->monthNum = data;
    temp->nextMonth = NULL;

    if(firstMonth == NULL)
    {
        firstMonth = temp;
    }
    else
    {
        month *a = firstMonth;
        while(a->nextMonth != NULL)
        {
            a = a->nextMonth;
        }
        a->nextMonth = temp;
    }
    
    if(data == 12)
    {
        temp->nextMonth = firstMonth;
    }
}

void daysofMonth(void)
{
    month *temp = firstMonth;

    int daisy[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for(int i = 0; i<12; i++)
    {
        temp->howManyDay = daisy[i];
        temp = temp->nextMonth;
    }
}

void createDay(int data)
{
    day *temp = (day *) malloc(sizeof(day));
    temp->dayNum = data;
    temp->nextDay = NULL;

    if(firstDay == NULL)
    {
        firstDay = temp;
    }
    else
    {
        day *a = firstDay;
        while(a->nextDay != NULL)
        {
            a = a->nextDay;
        }
        a->nextDay = temp;
    }

    if(data == 7)
    {
        temp->nextDay = firstDay;
    }
}

void clearMemory(void)
{
    month *a = firstMonth;
    day *b = firstDay;

    while(a->nextMonth != firstMonth)
    {
        a = a->nextMonth;
    }
    a->nextMonth = NULL;

    while(b->nextDay != firstDay)
    {
        b = b->nextDay;
    }
    b->nextDay = NULL;

    while(firstDay != NULL)
    {
        day *tempDay = firstDay->nextDay;
        free(firstDay);
        firstDay = tempDay;
    }
    while(firstMonth != NULL)
    {
        month *tempMonth = firstMonth->nextMonth;
        free(firstMonth);
        firstMonth = tempMonth;
    }
}