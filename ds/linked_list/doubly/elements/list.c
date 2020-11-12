#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "functions.h"

int main(void)
{
    printf("Commands:  add , remove , display , invert , position\n");
    printf("Press e to exit.\n\n");
    
    int check = 0, added = 0, removed = 0, inverted = 0, pos = 0;
    char input[9];
    const char *commands[6];
    commands[0] = "add";
    commands[1] = "remove";
    commands[2] = "display";
    commands[3] = "invert";
    commands[4] = "position";
    commands[5] = "e";

    cmd:

    scanf("%s", input);

    if(strcmp(input, commands[0]) == 0)
    {
        int pos, data;
        printf("Position to add element: ");
        scanf("%d", &pos);
        printf("Data: ");
        scanf("%d", &data);

        check = insertNode(pos, data);
        if(check == -1)
        {
            printf("Invalid position. There are currently %d elements in the list\n", totalNode);
        }
        else
        {
            printf("Element added!\n");
            added++;
        }
    }
    else if(strcmp(input, commands[1]) == 0)
    {
        int pos;
        printf("Position of the element to be removed: ");
        scanf("%d", &pos);

        check = deleteNode(pos);
        if(check == -1)
        {
            printf("Invalid position. There are currently %d elements in the list\n", totalNode);
        }
        else
        {
            printf("Element removed!\n");
            removed++;
        }
    }
    else if(strcmp(input, commands[2]) == 0)
    {
        displayList();
        printf("\n");
    }
    else if(strcmp(input, commands[3]) == 0)
    {
        int check;
        printf("Your list will be inverted:\n");
        displayListReverse();
        printf("Yes: 1, No: 0:\t");
        scanf("%d", &check);

        if(check == 1)
        {
            invertList();
            inverted++;
        }
        else
        {
            printf("\n");
        }
    }
    else if(strcmp(input, commands[4]) == 0)
    {
        changePosition();
        pos++;
        printf("\n");
    }
    else if(strcmp(input, commands[5]) == 0)
    {
        printf("Exiting...\n");
        sleep(2);
        printf("Report: %d elements has been added.\n", added);
        printf("\t%d elements has been removed.\n", removed);
        printf("\tList has been inverted %d times.\n", inverted);
        printf("\tPosition of the elements has been changed %d times.\n", pos);
        
        sleep(1);
        freeList();
        printf("\n\t\t%d elements are freed\n", totalNode);

        return 0;
    }
    else
    {
        printf("Commands:  add , remove , display , invert , position\n");
        printf("Press e to exit.\n\n");
    }

    goto cmd;
}