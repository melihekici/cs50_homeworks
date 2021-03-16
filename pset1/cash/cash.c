#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    /*Variable Declaration */
    float dollars;

    /*Get Change owed input from user until a non-negative number is given*/
    do
    {
        dollars = get_float("Change owed:");
    }
    while (dollars <= 0);

    /*Converting dollars to the cent and rounding up the number to deal with computer division errors */
    int cent = round(100 * dollars);

    /*Finding how many 25 cents exist in given cent, updating cent by remained */
    int c_25 = floor(cent / 25);
    cent = cent - 25 * c_25;

    /*Finding how many 25 cents exist in remained, updating cent by remained */
    int c_10 = floor(cent / 10);
    cent = cent - 10 * c_10;

    /*Finding how many 25 cents exist in remained, updating cent by remained */
    int c_5 = floor(cent / 5);
    cent = cent - 5 * c_5;

    /*Finding how many 25 cents exist in remained change owned*/
    int c_1 = floor(cent);

    printf("%i\n", c_25 + c_10 + c_5 + c_1);

}