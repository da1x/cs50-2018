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
        return 1;
    }

    //Get user plain text
    string plainText = get_string("plaintext: ");

    //string key number
    string keyString = argv[1];
    int keyLen = strlen(keyString);

    //encrypt with value that was given
    printf("ciphertext: ");

    for (int i = 0, j = 0, n = strlen(plainText); i < n; i++)
    {
        char letter = plainText[i];
        int key = tolower(keyString[j % keyLen]) - 'a';
        if (isalpha(letter))
        {
            //check if its upper or lower
            if (isupper(letter))
            {
                letter = ((letter - 65) + key) % 26;
                letter = letter + 65;
                printf("%c", letter);
                j++;
            }
            else
            {
                letter = ((letter - 97) + key) % 26;
                letter = letter + 97;
                printf("%c", letter);
                j++;
            }
        }
        else
        {
            printf("%c", letter);
        }
    }
    printf("\n");
}