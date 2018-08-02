#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[1])
{
    char plainText[100];

    if (argc == 2)
    {
        do
        {
            //prompt the user for a paintext
            printf("plaintext: ");
            scanf("%s", plainText);
            printf("%s\n", argv[1]);
        } while (isalpha(plainText));
    }
    else
    {
        //Exit the program if the user doesnt give the right values that we asked for
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    //encrypt with value that was given
    printf("ciphertext: ");
}