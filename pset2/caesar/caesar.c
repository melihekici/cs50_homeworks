#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int digit_count(int number);

int main(int argc, string argv[])
{
    int length1;
    int length2;
    int number;

    if (argc != 2)//Check if only one argument is given or not during execution
    {
        //If given more than one argument or given zero argument then returns an error
        printf("Please enter only one argument.\n");
        return 1;
    }
    else //If only one argumen is given
    {
        number = atoi(argv[1]); //Assign given argument to number variable
        length2 = digit_count(number); //Assign the number of digits in the given argumen to length2 variable
        length1 = strlen(argv[1]); //Assign the length of given number in length1 variable
    }

    /*Checks if only one argument is given. if not returns an error and ends. */
    if (argc != 2)
    {
        printf("Please enter only one argument.\n");
        return 1;
    }
    /*Checks if the argument given is a number. If not, returns an error and ends */
    else if (atoi(argv[1]) == 0 || length2 != (int)strlen(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        /*Assigning the text that is given by the user to variable plain */
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");
        /*Calculating the lenght of the input given by the user to use it as upperbound if iterator in for loop */
        int length = strlen(plain);

        for (int i = 0; i < length; i++)
        {
            /*If the character is an Uppercase letter, it will encrypt it here */
            if (plain[i] >= 65 && plain[i] <= 90)
            {
                int asd = (int)plain[i] + atoi(argv[1]) - 64;
                asd = asd % 26;
                printf("%c", asd + 64);
            }
            /*If the character is a lowercase letter, it will encrypt it here */
            else if (plain[i] >= 97 && plain[i] <= 122)
            {
                int asd = (int)plain[i] + atoi(argv[1]) - 96;
                asd = asd % 26;
                printf("%c", asd + 96);
            }
            /*If the character is not a letter in the alphabet, then it will be printed as it is */
            else
            {
                printf("%c", plain[i]);
            }
        }
        /*Moves to the next line after all printings are done */
        printf("\n");
    }
    return 0;

}

int digit_count(int number)
{
    int counter = 0;
    while (number > 0)
    {
        number = floor(number / 10);
        counter++;
    }
    return counter;
}
