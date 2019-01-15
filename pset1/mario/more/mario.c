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
            for (int j = 0; j < height; j++) //height
            {
                //Left pyramid
                for (int i = 0; i < numberOfSpace; i++)
                {
                    printf(" ");
                }

                for (int k = 0; k < height - numberOfSpace; k++)
                {
                    printf("#");
                }

                //Gap
                for (int m = 0; m < 2; m++)
                {
                    printf(" ");
                }

                //Right pyramid
                for (int k = 0; k < height - numberOfSpace; k++)
                {
                    printf("#");
                }
                numberOfSpace--;

                printf("\n");
            }
            break;
        }
    } while (true);
}
