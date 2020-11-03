#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

#define Block_size 512
#define File_name_size 8

bool jpg_start(BYTE Buffer []);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE* infile = fopen (argv[1], "r");
    if (infile == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    BYTE Buffer[Block_size];
    bool first_jpg = false;
    int file_count = 0;

    FILE* outfile;
    while(fread(Buffer, Block_size, 1, infile))
    {
     if (jpg_start(Buffer))
     {
         if(!first_jpg)
         {
             first_jpg = true;
         }
         else
         {
             fclose(outfile);
         }
         char file_name[File_name_size];
         sprintf (file_name, "%03i.jpg", file_count);
         file_count++;

         outfile = fopen(file_name, "w");
            if (outfile== NULL)
            {
                return 1;
            }
        fwrite (Buffer, Block_size, 1, outfile);
     }
     else if (first_jpg)
     {
         fwrite(Buffer, Block_size, 1, outfile);
     }
    }
    fclose(infile);
    fclose(outfile);

    return 0;
}

bool jpg_start(BYTE Buffer[])
{
    return (Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff && (Buffer[3] & 0xf0) == 0xe0);
}
