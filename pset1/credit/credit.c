#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long CardNum = 0, TempNum;
    int counter = 0;

    do
    {
        CardNum = get_long_long("Number: ");
    } while (CardNum <= 0);

    //Count how many digits
    TempNum = CardNum;
    while (TempNum > 0)
    {
        TempNum = TempNum / 10;
        counter++;
    }

    //Check if its 13/15/16 Digits
    /*if (counter != 13 && counter != 15 && counter != 16)
    {
        printf("INVALID\n");
    }*/

    int digits[counter];
    //Get all the numbers
    for (int i = 0; i < counter; i++)
    {
        digits[i] = CardNum % 10;
        CardNum = CardNum / 10;
    }

    //Save CardNum to a different varible
    int userInput[counter];
    for (int l = 0; l < counter; l++)
    {
        userInput[l] = digits[l];
    }

    //Multiply everyother 2 digital by 2
    for (int j = 1; j < counter; j = j + 2)
    {
        digits[j] = digits[j] * 2;
    }

    int totalSum = 0;
    //Add All numbers together
    for (int k = 0; k < counter; k++)
    {
        totalSum += (digits[k] % 10) + ((digits[k] / 10) % 10);
    }

    //Check if the credit card is vaild opr not
    if (counter != 13 && counter != 15 && counter != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        if (totalSum % 10 != 0)
        {
            printf("INVALID\n");
        }

        if (counter == 15 && userInput[14] == 3)
        {
            if (userInput[13] == 4 || userInput[13] == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (counter == 13 && userInput[12] == 4)
        {
            printf("VISA\n");
        }
        else if (counter == 16)
        {
            if (userInput[15] == 5)
            {
                if (userInput[14] == 1 || userInput[14] == 2 || userInput[14] == 3 || userInput[14] == 4 || userInput[14] == 5)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (userInput[15] == 4)
            {
                printf("VISA\n");
            }
        }
    }
}