#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int key;
    string plainText;

    //plaintext
    if (argc == 2 && argv[1] != NULL)
    {
        //convert key to int
        key = atoi(argv[1]);

        do
        {
            //plaintext
            plainText = get_string("plaintext: ");
        }
        while (plainText[0] == '\0');
    }
    else
    {
        //Exit the program if the user doesnt give the right values that we asked for
        return 1;
    }

    //encipher
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        char letter = plainText[i];
        if (isalpha(letter))
        {
            //check if its upper or lower
            if (isupper(letter))
            {
                letter = ((letter - 65) + key) % 26;
                letter = letter + 65;
                printf("%c", letter);
            }
            else
            {
                letter = ((letter - 97) + key) % 26;
                letter = letter + 97;
                printf("%c", letter);
            }
        }
        else
        {
            printf("%c", letter);
        }
    }
    printf("\n");
    //print ciphertext
}