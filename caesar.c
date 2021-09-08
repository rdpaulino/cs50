#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //checks for only 1 command-line argument
    if (argc != 2)
    {
        printf("Incorrect amount of command-line arguments.\n");
        return 1;
    }
    else
    {
        int key_length = strlen(argv[1]);

        //for every character inputted, it checks if it's a digit
        for (int i = 0; i < key_length; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        //converts the key from a string to an integer
        int k = atoi(argv[1]);
        char c;
        char p;

        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        int text_length = strlen(plaintext);
        for (int j = 0; j < text_length; j++)
        {
            p = plaintext[j];
            if (isupper(p) != 0)
            {
                //subtract to take the modulus
                p = p - 65;
                //modulus takes care of Z-A wraparound
                c = ((p + k) % 26) + 65;
                printf("%c", c);
            }
            else if (islower(p) != 0)
            {
                //subtract to take the modulus
                p = p - 97;
                //modulus takes care of Z-A wraparound
                c = ((p + k) % 26) + 97;
                printf("%c", c);
            }
            else
            {
                c = p;
                printf("%c", c);
            }
        }
        printf("\n");
        return 0;
    }

}