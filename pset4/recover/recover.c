#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Invalue input.\n");
        return 1;
    }
    //Open the raw data
    char *infile = argv[1];

    //Check if data cannot be open, then fprint stderr with return vaule of 2
    FILE *rawData = fopen(infile, "r");

    if (rawData == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }


    //buffer and check if it is null
    const int BUFFER_SIZE = 512;
    unsigned char buffer[BUFFER_SIZE];

    //Counter for filename
    FILE *img = NULL;

    //Check if jpg is open or not
    int jpgOpened = 0;

    //filename counter
    int filenameCounter = 0;

    //read file with fread(data, size, number, inputr)
    //Loop through the rawData - 512 at a time and check if there is a jpg
    while(fread(buffer, BUFFER_SIZE, 1, rawData) == 1)
    {
        //Check if it is a JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] && (buffer[3] & 0xf0) == 0xe0)
        {
            if(jpgOpened == 1)
            {
                //close image if we found the first img
                fclose(img);

            }
            else
            {
                //found the first jpg
                jpgOpened = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", filenameCounter);
            img = fopen(filename, "a");
            filenameCounter++;
        }

        //write out jpg
        if(jpgOpened == 1)
        {
            fwrite(&buffer, BUFFER_SIZE, 1,img);
        }

    }
    //close any files that are opened
    fclose(img);
    fclose(rawData);

    return 0;
}