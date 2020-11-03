#include "helpers.h"
#include <stdbool.h>
#include <math.h>

bool check_valid_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    float redXValue     = 0;
    float greenXValue   = 0;
    float blueXValue    = 0;
    float redYValue     = 0;
    float greenYValue   = 0;
    float blueYValue    = 0;

    int gX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int x, y;

    //scan every pixel
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            //find the neighbours of the pixel
            for (int a = -1; a<=1; a++)
            {
                for (int b = -1; b<=1; b++)
                {
                    //make sure that there will be no "out of bounds" errors
                    if(check_valid_pixel(i+a, j+b, height, width))
                    {
                        //multiply first element of the gX array and first element of the image
                        x = gX[a+1][b+1];

                        redXValue   += x * image[i+a][j+b].rgbtRed;
                        greenXValue += x * image[i+a][j+b].rgbtGreen;
                        blueXValue  += x * image[i+a][j+b].rgbtBlue;

                        y = gX[b+1][a+1];

                        redYValue   += y * image[i+a][j+b].rgbtRed;
                        greenYValue += y * image[i+a][j+b].rgbtGreen;
                        blueYValue  += y * image[i+a][j+b].rgbtBlue;
                    }
                }
            }

            int r = 0;
            int g = 0;
            int b = 0;

            int red     = round(sqrt(redXValue*redXValue + redYValue*redYValue));
            int green   = round(sqrt(greenXValue*greenXValue + greenYValue*greenYValue));
            int blue    = round(sqrt(blueXValue*blueXValue + blueYValue*blueYValue));

            if(red > 255)
                r = 255;
            else
               r = red;

            if(green  > 255)
                g = 255;
            else
                g = green;

            if(blue > 255)
                b = 255;
            else
                b = blue;

            tmp[i][j].rgbtRed = r;
            tmp[i][j].rgbtGreen = g;
            tmp[i][j].rgbtBlue = b;


            redXValue     = 0;
            greenXValue   = 0;
            blueXValue    = 0;
            redYValue     = 0;
            greenYValue   = 0;
            blueYValue    = 0;
        }
    }

    //copy the tmp to the original image
    for (int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}




// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // averages the color intensity and then applies the same value to all the colors to get gray
            rgbGray = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.000);

            image[j][i].rgbtBlue = rgbGray;
            image[j][i].rgbtGreen = rgbGray;
            image[j][i].rgbtRed = rgbGray;
        }
    }
}

// stops max value at 255 preventing overflow
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //use of a temporary array to swap values
    int temp[3];
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            temp[0] = image[j][i].rgbtBlue;
            temp[1] = image[j][i].rgbtGreen;
            temp[2] = image[j][i].rgbtRed;

            // swap pixels with the ones on the opposite side of the picture and viceversa
            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;

            image[j][width - i - 1].rgbtBlue = temp[0];
            image[j][width - i - 1].rgbtGreen = temp[1];
            image[j][width - i - 1].rgbtRed = temp[2];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            // averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}