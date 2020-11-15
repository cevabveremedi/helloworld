/*
    it's working but has to be optimised!!
    Error messages are wrong.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int line;
    int letter;
    char type;
}parantheses;

char balanced(char a);

int main(void)
{
    FILE* fp = fopen("data.txt", "r");
    if(fp == NULL)
    {
        printf("Cannot open the file!\n");
        return 1;
    }

    parantheses array[4000]; 
    //for storing the info of all parantheses in the data.txt

    char ch1, ch2;
    ch2 = fgetc(fp);
    
    int currLine = 1, currLetter = 2;
    //index of the location of the parantheses

    int num = 0; //total

    while(ch2 != EOF)
    {
        ch1 = ch2;
        ch2 = fgetc(fp);

        if(ch2 == '\n')
        {
            currLine++;
            currLetter = 0;
        }

        if((ch2 == '(') || (ch2 == ')') || (ch2 == '{') || 
           (ch2 == '}') || (ch2 == '[') || (ch2 == ']'))
        {
            array[num].letter = currLetter;
            array[num].line = currLine;
            array[num].type = ch2;
            num++;
        }
        if(ch2 == '$')
        {
            int breakpoint = 1;
            breakpoint++;
        }

        currLetter++;
    }
    //found everything needed

    fclose(fp);

    parantheses stack[num]; //stores the open parantheses '(' '[' '{'
    int head = 0;
    int errorCount = 0;

    for(int i = 0; i<num; i++)
    {
        char ch = array[i].type;

        if((ch == '(') || (ch == '{') || (ch == '['))
        {
            stack[head] = array[i];
            head++;
        }
        else
        {
            char rev = balanced(ch); 
            // change closed parantheses to open parantheses 
            // to check if it's correct type.

            if(rev == stack[head-1].type)
            {
                head--; //if it's correct, then current head pops.
            }
            else
            {
                int a = array[i].line;
                int b = array[i].letter;
                char c = array[i].type;
                
                printf("Error in line %d:%d   '%c'\n", a, b, c);
                errorCount++;
            }
        }
    }

    if(head != 0) //if there are any open parantheses left
    {
        int i = 0;
        while(head != 0)
        {
            errorCount++;
            int a = stack[i].line; 
            int b = stack[i].letter; 
            char miss = balanced(stack[i].type);

            printf("Error in line %d:%d   ", a, b);
            printf("Missing parantheses: '%c'\n", miss);
            head--;
            i++;
        }
    }

    if(errorCount == 0)
    {
        printf("Parantheses are balanced!\n");
    }
    else
    {
        printf("\nTotal errors: %d\n", errorCount);
    }
}

char balanced(char a)
{
    if(a == ')')
        return '(';
    else if(a == '}')
        return '{';
    else if(a == ']')
        return '[';
    else if(a == '[')
        return ']';
    else if(a == '{')
        return '}';
    else if(a == '(')
        return ')';
}