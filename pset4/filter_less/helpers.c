#include "helpers.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Creating Variables to store original colors and sepia colors
    float org_red;
    float org_green;
    float org_blue;
    int sepia_red;
    int sepia_green;
    int sepia_blue;

    //For each pixel, calculating and assiging colors
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Storing the original colors of pixel (h,w) to related variables
            org_red = image[h][w].rgbtRed;
            org_green = image[h][w].rgbtGreen;
            org_blue = image[h][w].rgbtBlue;

            //Calculating sepia colors using original colors
            sepia_red = (int)(.393 * org_red + .769 * org_green + .189 * org_blue + .5);
            sepia_green = (int)(.349 * org_red + .686 * org_green + .168 * org_blue + .5);
            sepia_blue = (int)(.272 * org_red + .534 * org_green + .131 * org_blue + .5);

            //if sepia colors are greater than 255 then we set them to 255
            if (sepia_red > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = sepia_red;
            }

            if (sepia_green > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = sepia_green;
            }

            if (sepia_blue > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = sepia_blue;
            }
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
