#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int unique_count(char *s1);
int digit_count(int number);
int check_alphabetic(char *s1);

int main(int argc, string argv[])
{
    /*Variable declaration */
    int length1;
    int length2;
    int number;
    int uniq;
    int non_alph;

    if (argc != 2)
    {
        if (argc == 1)
        {
            printf("You need to enter a key.\n");
            return 1;
        }
        else
        {
            printf("Please enter only one argument.\n");
            return 1;
        }
    }
    else
    {
        uniq = unique_count(argv[1]);
        length1 = strlen(argv[1]);
        non_alph = check_alphabetic(argv[1]);
    }

    if (length1 != 26)
    {
        printf("Input should be 26 characters without any spaces in-between.\n");
        return 1;
    }
    else if (uniq > 0)
    {
        printf("Your input has duplicate characters\n");
        return 1;
    }
    else if (non_alph != length1)
    {
        printf("Non-Alphabetic characters exist in your key. Please enter alphabetic characters only.\n");
        return 1;
    }
    else
    {
        number = atoi(argv[1]);
        length2 = digit_count(number);
    }

    /*Checks if only one argument is given. if not returns an error and ends. */
    if (argc != 2)
    {
        printf("Please enter only one argument.\n");
        return 1;
    }
    /*Checks if the argument given is a number. If not, returns an error and ends */
    else if (false)
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
                int asd = (int)plain[i] - 65;
                /*If the refrence letter is also uppercase */
                if ((int)argv[1][asd] >= 65 && (int)argv[1][asd] <= 90)
                {
                    printf("%c", argv[1][asd]);
                }
                /*Else if the refrence letter is lowercase */
                else if ((int)argv[1][asd] >= 97 && (int)argv[1][asd] <= 122)
                {
                    printf("%c", argv[1][asd] - 32);
                }
                else
                {
                    printf("%c", plain[i]);
                }
            }

            /*If the character is a lowercase letter, it will encrypt it here */
            else if (plain[i] >= 97 && plain[i] <= 122)
            {
                /*If the refrence letter is also a lowercase */
                int asd = (int)plain[i] - 97 ;
                if ((int)argv[1][asd] >= 97 && (int)argv[1][asd] <= 122)
                {
                    printf("%c", argv[1][asd]);
                }

                /*If the refrence letter is Uppercase then convert cipher to lowercase version */
                else if ((int)argv[1][asd] >= 65 && (int)argv[1][asd] <= 90)
                {
                    printf("%c", argv[1][asd] + 32);
                }
                else
                {
                    printf("%c", plain[i]);
                }
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

/*Function that is used to count number of digits inside a number */
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


/*Function that is used to count number of duplicate characters inside a string. */
int unique_count(char *s1)
{
    int i;
    int j;
    int leng = strlen(s1);
    int duplicate = 0;

    /* For each character in the plain text, we check if it is same as the other characters */
    for (i = 0; i < leng; i++)
    {
        char current = s1[i];
        for (j = i + 1; j < leng; j++)
        {
            if (current == s1[j])
            {
                /*We increment duplicate variable by 1 each time we encounter a match */
                duplicate += 1;
            }
        }
    }


    /*Then function returns the number of duplicate characters exist in the string */
    return duplicate;
}

int check_alphabetic(char *s1)
{
    int i;
    int counter = 0;
    for (i = 0; i < strlen(s1); i++)
    {
        if ((s1[i] >= 65 && s1[i] <= 90) || (s1[i] >= 97 && s1[i] <= 122))
        {
            counter++;
        }
    }
    return counter;
}