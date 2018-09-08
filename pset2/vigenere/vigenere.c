#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[1])
{

    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]) == false)
            {
                printf("Non-alphabetical characters are not allow\n");
                return 1;
            }
        }
    }
    else
    {
        //Exit the program if the user doesnt give the right values that we asked for
        printf("Usage: ./vigenere k\n");
        return 2;
    }

    //Get user plain text
    int plainText = get_int("plaintext: ");
    printf("%i", plainText);

    //string key number

    //encrypt with value that was given
    printf("ciphertext: \n");
}