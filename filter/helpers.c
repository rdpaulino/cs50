#include "helpers.h"
#include "stdio.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0;
    RGBTRIPLE copy[height][width];

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            copy[i][j] = image[i][j];

            float Rcopy = copy[i][j].rgbtRed;
            float Gcopy = copy[i][j].rgbtGreen;
            float Bcopy = copy[i][j].rgbtBlue;

            avg = (Rcopy + Gcopy + Bcopy) / 3;

            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE left[height][width];
    RGBTRIPLE right[height][width];

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            left[i][j] = image[i][j];
            right[i][j] = image[i][width - j - 1];
        }
    }
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            image[i][j] = right[i][j];
            image[i][width - j - 1] = left[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    //copy image
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            copy[i][j] = image[i][j];
            float Rcopy = copy[i][j].rgbtRed;
            float Gcopy = copy[i][j].rgbtGreen;
            float Bcopy = copy[i][j].rgbtBlue;
        }
    }

    //manipulate/blur copy
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            float adjPixels = 0;
            float avgR = 0;
            float avgG = 0;
            float avgB = 0;

            // corner pixel
            if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
            {
                adjPixels = 4;

                //bottom row
                if (i == 0)
                {
                    //left column
                    if (j == 0)
                    {
                        //bottom left pixel
                        avgR = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / adjPixels);
                        avgG = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                                     adjPixels);
                        avgB = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / adjPixels);

                        if (avgR >= 255)
                        {
                            avgR = 255;
                        }
                        if (avgG >= 255)
                        {
                            avgG = 255;
                        }
                        if (avgB >= 255)
                        {
                            avgB = 255;
                        }

                        image[i][j].rgbtRed = avgR;
                        image[i][j].rgbtGreen = avgG;
                        image[i][j].rgbtBlue = avgB;
                    }

                    //right column
                    else
                    {
                        //bottom right pixel
                        avgR = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / adjPixels);
                        avgG = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                     adjPixels);
                        avgB = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / adjPixels);

                        if (avgR >= 255)
                        {
                            avgR = 255;
                        }
                        if (avgG >= 255)
                        {
                            avgG = 255;
                        }
                        if (avgB >= 255)
                        {
                            avgB = 255;
                        }

                        image[i][j].rgbtRed = avgR;
                        image[i][j].rgbtGreen = avgG;
                        image[i][j].rgbtBlue = avgB;
                    }
                }
                //top row
                else
                {
                    //top left pixel
                    if (j == 0)
                    {
                        avgR = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / adjPixels);
                        avgG = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                                     adjPixels);
                        avgB = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / adjPixels);

                        if (avgR >= 255)
                        {
                            avgR = 255;
                        }
                        if (avgG >= 255)
                        {
                            avgG = 255;
                        }
                        if (avgB >= 255)
                        {
                            avgB = 255;
                        }

                        image[i][j].rgbtRed = avgR;
                        image[i][j].rgbtGreen = avgG;
                        image[i][j].rgbtBlue = avgB;
                    }
                    //top right pixel
                    else
                    {
                        avgR = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / adjPixels);
                        avgG = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                                     adjPixels);
                        avgB = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / adjPixels);

                        if (avgR >= 255)
                        {
                            avgR = 255;
                        }
                        if (avgG >= 255)
                        {
                            avgG = 255;
                        }
                        if (avgB >= 255)
                        {
                            avgB = 255;
                        }

                        image[i][j].rgbtRed = avgR;
                        image[i][j].rgbtGreen = avgG;
                        image[i][j].rgbtBlue = avgB;
                    }
                }
            }

            // top/bottom edge pixels
            else if ((i == 0 || i == height - 1) && (j != 0 || j != width - 1))
            {
                adjPixels = 6;

                //bottom edge pixels
                if (i == 0)
                {
                    avgR = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i +
                                 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / adjPixels);
                    avgG = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i +
                                 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / adjPixels);
                    avgB = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i +
                                 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / adjPixels);

                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }

                    image[i][j].rgbtRed = avgR;
                    image[i][j].rgbtGreen = avgG;
                    image[i][j].rgbtBlue = avgB;
                }
                //top edge pixels
                else
                {
                    avgR = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j
                                 - 1].rgbtRed + copy[i][j - 1].rgbtRed) / adjPixels);
                    avgG = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen  + copy[i -
                                 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) / adjPixels);
                    avgB = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j
                                 - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / adjPixels);

                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }

                    image[i][j].rgbtRed = avgR;
                    image[i][j].rgbtGreen = avgG;
                    image[i][j].rgbtBlue = avgB;
                }
            }
            // left/right edge pixel
            else if ((j == 0 || j == width - 1) && (i != 0 || i != height - 1))
            {
                adjPixels = 6;

                //left edge pixels
                if (j == 0)
                {
                    avgR = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i -
                                 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / adjPixels);
                    avgG = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i -
                                 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / adjPixels);
                    avgB = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i -
                                 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / adjPixels);

                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }

                    image[i][j].rgbtRed = avgR;
                    image[i][j].rgbtGreen = avgG;
                    image[i][j].rgbtBlue = avgB;
                }
                //right edge pixels
                else
                {
                    avgR = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i - 1][j -
                                 1].rgbtRed + copy[i - 1][j].rgbtRed) / adjPixels);
                    avgG = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i -
                                 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) / adjPixels);
                    avgB = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j
                                 - 1].rgbtBlue + copy[i - 1][j].rgbtBlue) / adjPixels);

                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }

                    image[i][j].rgbtRed = avgR;
                    image[i][j].rgbtGreen = avgG;
                    image[i][j].rgbtBlue = avgB;
                }
            }
            // middle pixel
            else
            {
                adjPixels = 9;

                avgR = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i +
                             1][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                             adjPixels);
                avgG = round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i
                             + 1][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j +
                             1].rgbtGreen) / adjPixels);
                avgB = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i +
                             1][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                             adjPixels);

                if (avgR >= 255)
                {
                    avgR = 255;
                }
                if (avgG >= 255)
                {
                    avgG = 255;
                }
                if (avgB >= 255)
                {
                    avgB = 255;
                }

                image[i][j].rgbtRed = avgR;
                image[i][j].rgbtGreen = avgG;
                image[i][j].rgbtBlue = avgB;
            }
        }
    }

    return;
}