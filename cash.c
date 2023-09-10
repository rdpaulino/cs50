#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    int change;

    do
    dollars = get_float("Change owed: ");
    while (dollars < 0);

    long coins = round(dollars * 100);

    for (long q = coins; q >= 25; q = q - 25)
    {
        quarters++;
        coins = coins - 25;
    }
    for (long d = coins; d >= 10; d = d - 10)
    {
        dimes++;
        coins = coins - 10;
    }
    for (long n = coins; n >= 5; n = n - 5)
    {
        nickels++;
        coins = coins - 5;
    }
    while (coins > 0)
    {
        pennies++;
        coins = coins - 1;
    }
    change = quarters + dimes + nickels + pennies;
    printf("%i\n",change);
}
