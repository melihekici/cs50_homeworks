#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Creating a buffer size of 512 Bytes using type BYTE
    BYTE buffer[512];
    //pic_name is going to be the new jpeg file that is going to be created and will be written into
    //Allocation memory of size 8 to pic_name because the name of the new jpeg file is going to be 8 chars.
    char *pic_name = malloc(8);
    bool pic_open = false;

    //Error checking. If number of arguments given is not equal to two, print the error message then return and terminate.
    if (argc != 2)
    {
        printf("Print enter exactly one input.\n");
        return 1;
    }

    else if (argv[1] == NULL)
    {
        printf("Print the name of the memory card.\n");
        return 1;
    }

    else
    {
        //Open the memory card and save it to the variable f
        //create a pointer to to image file that is going to be creater in latter steps.
        FILE *f = fopen(argv[1], "r");
        FILE *img = NULL;
        int i = 0;

        while (fread(buffer, 512, 1, f) > 0)
        {
            //if this is the start of a jpeg file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                //if this is the first jpeg
                if (i == 0)
                {
                    sprintf(pic_name, "%03i.jpg", i);
                    img = fopen(pic_name, "w");
                    fwrite(buffer, 512, 1, img);
                    i++;
                    pic_open = true;
                }
                //if it is not the first jpeg
                else
                {
                    //we close the image file
                    fclose(img);
                    sprintf(pic_name, "%03i.jpg", i);
                    img = fopen(pic_name, "w");
                    fwrite(buffer, 512, 1, img);
                    i++;
                }
            }
            //if the block is not the start of a new jpeg file and a jpeg file is allready open
            else if (pic_open)
            {
                //then keep writing to the open file
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    free(pic_name);
    return 0;
}

