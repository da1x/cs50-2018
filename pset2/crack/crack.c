#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[1])
{

    string letter = "abcdefghijklmnopqrstwxyzABCDEFGHIJKLMNOPQRSTWXYZ";
    string hash = NULL;
    char key[6];

    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    else
    {
        hash = argv[1];
    }

    //Salt - first 1 letters of hash
    char salt[3];
    salt[0] = hash[0];
    salt[1] = hash[1];

    //Checks a-Z
    for (int i = 0; i < 52; i++)
    {
        key[0] = letter[i];
        key[1] = '\0';

        if (strcmp(crypt(key, salt), hash) == 0)
        {
            printf("%s\n", key);
            return 0;
        }
    }

    //aa-ZZ
    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            key[0] = letter[i];
            key[1] = letter[j];
            key[2] = '\0';

            if (strcmp(crypt(key, salt), hash) == 0)
            {
                printf("%s\n", key);
                return 0;
            }
        }
    }

    //aaa-ZZZ
    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            for (int k = 0; k < 52; k++)
            {
                key[0] = letter[i];
                key[1] = letter[j];
                key[2] = letter[k];
                key[3] = '\0';

                if (strcmp(crypt(key, salt), hash) == 0)
                {
                    printf("%s\n", key);
                    return 0;
                }
            }
        }
    }

    //aaaa-ZZZZ
    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            for (int k = 0; k < 52; k++)
            {
                for (int l = 0; l < 52; l++)
                {
                    key[0] = letter[i];
                    key[1] = letter[j];
                    key[2] = letter[k];
                    key[3] = letter[l];
                    key[4] = '\0';

                    if (strcmp(crypt(key, salt), hash) == 0)
                    {
                        printf("%s\n", key);
                        return 0;
                    }
                }
            }
        }
    }

    //aaaaa-ZZZZZ
    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            for (int k = 0; k < 52; k++)
            {
                for (int l = 0; l < 52; l++)
                {
                    for (int m = 0; m < 52; m++)
                    {
                        key[0] = letter[i];
                        key[1] = letter[j];
                        key[2] = letter[k];
                        key[3] = letter[l];
                        key[4] = letter[m];
                        key[5] = '\0';

                        if (strcmp(crypt(key, salt), hash) == 0)
                        {
                            printf("%s\n", key);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("No password match\n");
    return 1;
}