#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: Could not read image\n");
        return 1;
    }

    BYTE buffer[512];
    FILE *outputImg;
    char imgName[100];
    int imgCount = 0;

    //file pointer at the end of file to get size
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    //resetting file pointer to beginning
    fseek(file, 0, SEEK_SET);

    //iterate on every 512-byte block
    for (int i = 0; i < fileSize / 512; i++)
    {
        //read 512 block into buffer
        fread(buffer, 512, 1, file);

        //if JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            //naming file ###.jpg
            sprintf(imgName, "%03i.jpg", imgCount);

            //creating output file
            outputImg = fopen(imgName, "w");

            //if first JPEG
            if (imgCount == 0)
            {
                //writing JPEG to output file
                fwrite(buffer, 512, 1, outputImg);

            }
            //if not first JPEG
            else if (imgCount != 0)
            {

                fclose(outputImg);

                //naming file ###.jpg
                sprintf(imgName, "%03i.jpg", imgCount);

                //creating output file
                outputImg = fopen(imgName, "w");

                //writing JPEG to output file
                fwrite(buffer, 512, 1, outputImg);

            }

            imgCount++;
        }
        //if not JPEG
        else if (imgCount != 0)
        {
            fwrite(buffer, 512, 1, outputImg);
        }

    }

    fclose(file);
    fclose(outputImg);
}
