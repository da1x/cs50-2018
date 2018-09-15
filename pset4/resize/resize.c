// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //Get a positive interger less than or equal to 100
    int n = atoi(argv[1]);

    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Usage: Integer must be between 0 - 100\n");
        return 5;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER, also make a copy for editing
    BITMAPFILEHEADER bf, bfResize;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfResize = bf;

    // read infile's BITMAPINFOHEADER, also make a copy for editing
    BITMAPINFOHEADER bi, biResize;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    biResize = bi;

    //Mulitply the width and height with prompted value n
    biResize.biWidth = bi.biWidth * n;
    biResize.biHeight = bi.biHeight * n;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines, one for normal and one for resized image
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingResize = (4 - (biResize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Calculate the resized images for bfSize and bfSizeImage
    biResize.biSizeImage = ((sizeof(RGBTRIPLE) * biResize.biWidth) + paddingResize) * abs(biResize.biHeight);
    bfResize.bfSize = biResize.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    // write outfile's BITMAPFILEHEADER with the resized bf and bi
    fwrite(&bfResize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Copy the RGBTRIPLES by value n by using a for loop(rows)
        for (int l = 0; l < n; l++)
        {

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //Copy the RGBTRIPLES by value n by using a for loop (colums)
                for (int m = 0; m < n; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingResize; k++)
            {
                fputc(0x00, outptr);
            }

            //go back to first pixel to copy downward
            if (l < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
