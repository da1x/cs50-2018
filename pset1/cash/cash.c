#include <stdio.h>
#include <cs50.h>
#include <math.h>

/*Coins:
    Quarter 25
    Dime 10
    Nickel 5
    Penny 1
*/

int main(void)
{
    int coin = 0;

    float change;
    do
    {
        change = get_float("Change: ");
    }
    while (change < 0);

    //Change to input to all cents
    change = roundf(change * 100);
    //Use the largest coin possible
    //How many coins to be returnwd
    //as well as remains of amounts

    while (change >= 25)
    {
        coin++;
        change -= 25;
    }

    while (change >= 10)
    {
        coin++;
        change -= 10;
    }

    while (change >= 5)
    {
        coin++;
        change -= 5;
    }

    while (change >= 1)
    {
        coin++;
        change -= 1;
    }

    //Print the final numbers of coins
    printf("%i\n", coin);
}