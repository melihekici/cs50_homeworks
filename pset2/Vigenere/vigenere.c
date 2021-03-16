#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int digit_count(int number);
bool plain_checker(string plain);


int main(int argc, string argv[])
{
    if (argc != 2) // Check if only one argument is given or not during execution
    {
        // If given more than one argument or given zero argument then returns an error
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else if (atoi(argv[1]) == 0 && plain_checker(argv[1]) == false) // Checks if the argument given is a number. If not, returns an error and ends
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else
    {
        /*Assigning the text that is given by the user to variable plain */
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");
        /*Calculating the lenght of the input given by the user to use it as upperbound if iterator in for loop */
        int plainLength = strlen(plain);
        int keyLength = strlen(argv[1]);

        int increment = 0;
        char currentKey;
        int keyCounter=0;
        for (int i = 0; i < plainLength; i++)
        {
            currentKey = argv[1][keyCounter % keyLength];

            /*If key character is an Uppercase character, it will calculate the increment value here*/
            if (currentKey >= 65 && currentKey <= 90)
            {
                increment = (int)(currentKey) - 65;
            }
            /*Else if key character is a lower case character, it will calculate the increment value here*/
            else if (currentKey >= 97 && currentKey <= 122)
            {
                increment = (int)(currentKey) - 97;
            }
            else{
                increment = 0;
            }


            /*If the character is an Uppercase letter, it will encrypt it here */
            if (plain[i] >= 65 && plain[i] <= 90)
            {
                int asd = (int)plain[i] + increment - 65;
                asd = asd % 26;
                printf("%c", asd + 65);
                keyCounter++;
            }
            /*If the character is a lowercase letter, it will encrypt it here */
            else if (plain[i] >= 97 && plain[i] <= 122)
            {
                int asd = (int)plain[i] + increment - 97;
                asd = asd % 26;
                printf("%c", asd + 97);
                keyCounter++;
            }
            /*If the character is not a letter in the alphabet, then it will be printed as it is */
            else
            {
                printf("%c", plain[i]);
            }
        }
    }
    printf("\n");
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

bool plain_checker(string plain)
{
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isdigit(plain[i])){
            return false;
        }
    }
    return true;
}