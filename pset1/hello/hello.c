#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /*Asking for the name and assigning it to string variable name  */
    string name = get_string("What is your name?\n");
    /*Says the name given by the user after saying hello */
    printf("hello, %s\n", name);
}