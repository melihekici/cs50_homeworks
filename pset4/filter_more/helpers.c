#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            average = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue + 1.5) / 3;
            image[h][w].rgbtRed = (int)average;
            image[h][w].rgbtGreen = (int)average;
            image[h][w].rgbtBlue = (int)average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Finding the middle point of width of the image
    int mid = width / 2;

    //Creating a temporary RGBTRIPLE type variable to be used while replacing pixels
    RGBTRIPLE temp;

    //Replacing each pixel with its horizontal reflection
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < mid; w++)
        {
            temp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_red;
    int avg_green;
    int avg_blue;
    int counter;

    RGBTRIPLE org_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            org_image[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Initializing the average of adjacent pixel colors to zero
            //Initializing the counter to zero which will count the number of adjacent pixels
            avg_red = 0;
            avg_green = 0;
            avg_blue = 0;
            counter = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (h + i < height && h + i >= 0 && w + j < width && w + j >= 0)
                    {
                        avg_red += org_image[h + i][w + j].rgbtRed;
                        avg_green += org_image[h + i][w + j].rgbtGreen;
                        avg_blue += org_image[h + i][w + j].rgbtBlue;
                        counter++;
                    }
                }
            }

            //Calculating average red, blue and green color for pixel (h,w) and rounding it to the nearest integer
            avg_red = (int)((avg_red + counter / 2) / counter);
            avg_green = (int)((avg_green + counter / 2) / counter);
            avg_blue = (int)((avg_blue + counter / 2) / counter);

            //Updating the pixel colors with the average values
            image[h][w].rgbtRed = avg_red;
            image[h][w].rgbtGreen = avg_green;
            image[h][w].rgbtBlue = avg_blue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Variable prototypes
    double gx_red;
    double gx_green;
    double gx_blue;
    double gy_red;
    double gy_green;
    double gy_blue;
    int new_red;
    int new_green;
    int new_blue;
    double gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    double gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //Keep the original image in org_image
    RGBTRIPLE org_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            org_image[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Set gx and gy values for each color to zero (Initializing)
            gx_red = 0;
            gx_green = 0;
            gx_blue = 0;
            gy_red = 0;
            gy_green = 0;
            gy_blue = 0;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    //
                    if (h + i < height && h + i >= 0 && w + j < width && w + j >= 0)
                    {
                        //Increment gx and gy of each color by given formula using adjacent pixels (if adjacent pixel is inside of the borders)
                        gx_red += (double)(org_image[h + i][w + j].rgbtRed) * (double)(gx[i + 1][j + 1]);
                        gx_green += (double)(org_image[h + i][w + j].rgbtGreen) * (double)(gx[i + 1][j + 1]);
                        gx_blue += (double)(org_image[h + i][w + j].rgbtBlue) * (double)(gx[i + 1][j + 1]);
                        gy_red += (double)(org_image[h + i][w + j].rgbtRed) * (double)(gy[i + 1][j + 1]);
                        gy_green += (double)(org_image[h + i][w + j].rgbtGreen * (double)(gy[i + 1][j + 1]));
                        gy_blue += (double)(org_image[h + i][w + j].rgbtBlue * (double)(gy[i + 1][j + 1]));
                    }
                }
            }
            
            //Calculating the new colors using gx and gy for each color
            new_red = (int)(sqrt(gx_red * gx_red + gy_red * gy_red) + 0.5);
            new_green = (int)(sqrt(gx_green * gx_green + gy_green * gy_green) + 0.5);
            new_blue = (int)(sqrt(gx_blue * gx_blue + gy_blue * gy_blue) + 0.5);
            
            //If found new colors are greater than 255, set them to 255
            if (new_red <= 255)
            {
                image[h][w].rgbtRed = new_red;
            }
            else
            {
                image[h][w].rgbtRed = 255;
            }

            if (new_green <= 255)
            {
                image[h][w].rgbtGreen = new_green;
            }
            else
            {
                image[h][w].rgbtGreen = 255;
            }

            if (new_blue <= 255)
            {
                image[h][w].rgbtBlue = new_blue;
            }
            else
            {
                image[h][w].rgbtBlue = 255;
            }
        }
    }

    return;
}
