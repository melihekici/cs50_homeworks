#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    /*Do while loop is going to take input until the user gives some number between 1 and 8 */
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    /*Looping over each row(i) up to the given integer by the user*/
    for (int i = 1; i <= n; i++)
    {
        /*For each row i, the first (n-i)th character will be space ( (n-i) is represented by k here ) */
        for (int k = 1; k <= n - i ; k++)
        {
            printf(" ");
        }

        /*After putting spaces to the ith row, we now will place the blocks(#) until we reach nth column */
        /*Notice that For every row we have placed (n-i) spaces And i blocks which are summed to n colums  */
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        /*After we placed (n-i) spaces And i blocks to ith row, we move on to the next line  */
        printf("\n");
    }
}