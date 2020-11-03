//////////////////////////
/************************/
/* CHANGE THE MAKEFILE! */
/************************/
//////////////////////////

#include <stdio.h>

int main (int argc, char *argv[])
{
    FILE *fp, *ft;
    char ch, ch1;
    if (argc < 3)
    {
        printf ("No file name given!\n");
        return 1;
    }

    fp = fopen (argv[1], "r");
    ft = fopen (argv[2], "w");
    if (fp == NULL)
    {
        printf ("Opening error!\n");
        return 1;
    }    
    if (ft == NULL)
    {
        printf ("Opening error!\n");
        return 1;
    }
    ch1 = fgetc (fp);
    while (ch1 != EOF)
    {
        ch = ch1;
        ch1 = fgetc (fp);

        if ((ch == '/') && (ch1 == '*')) 
        {
            ch1 = fgetc (fp);
            while ((ch != '*') && (ch1 != '/')) /* unroll until the end of comment*/
            {
                ch = ch1;
                ch1 = fgetc (fp);
            }
            ch = fgetc (fp);
            ch1 = fgetc (fp);
        }

        if((ch == '/') && (ch1 == '/'))
        {
            while(ch1 != '\n')
            {
                ch1 = fgetc (fp);
            }
            ch = ch1;
            ch1 = fgetc (fp);
        }

        putc (ch, ft);
    }
    fclose (fp);
    fclose (ft);
    return 0;
}