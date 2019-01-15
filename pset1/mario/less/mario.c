#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");

        int numberOfSpace = height - 1;
        if (height < 9 && height > 0)
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < numberOfSpace; j++)
                {
                    printf(" ");
                }

                for (int k = 0; k < height - numberOfSpace; k++)
                {
                    printf("#");
                }

                printf("\n");
                numberOfSpace--;
            }
            break;
        }
    } while (true);
}
