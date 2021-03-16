#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

int num_letters(string txt); //Function that gives number of letters in given text.
int num_sentences(string txt); //Function that gives number of sentences in given text.
int num_words(string txt); //Function that gives number of words in given text.

int main(void)
{
    /* Variable Declaration */
    float L; // Average number of letters per 100 words
    float S; // Average number of sentences per 100 words
    float index;

    string txt = get_string("Text: ");//Get the text as input from user

    L = num_letters(txt) / (float)num_words(txt) * 100;//Calculating the average number of letters per 100 words
    S = num_sentences(txt) / (float)num_words(txt) * 100;//Calculating the average number of sentences per 100 words
    //printf("L is: %f\n", L);
    //printf("S is: %f\n", S);
    //printf("text length %lu\n", strlen(txt));
    index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)(index + 0.5));
    }
}

int num_letters(string txt)
{
    int counter = 0;
    for (int i = 0; i < strlen(txt); i++)
    {
        if ((txt[i] >= 65 && txt[i] <= 90) || (txt[i] >= 97 && txt[i] <= 122))
        {
            counter++;
        }
    }
    //printf("Number of letters: %i\n", counter);
    return counter;
}

int num_sentences(string txt)
{
    int counter = 0;
    for (int i = 0; i < strlen(txt); i++)
    {
        if (txt[i] == 46 || txt[i] == 63 || txt[i] == 33)
        {
            counter++;
        }
    }
    //printf("Number of sentences: %i\n", counter);
    return counter;

}

int num_words(string txt)
{
    int counter = 1;
    for (int i = 0; i < strlen(txt); i++)
    {
        if (txt[i] == 32)
        {
            counter++;
        }
    }
    //printf("Number of words: %i\n", counter);
    return counter;
}
