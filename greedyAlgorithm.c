// Implementation of an Application of Greedy Algorithm in C Language
/*
    This program takes a list of coin values as command line arguments and reads the amount for which 
    we want to make change from the standard input. It then uses a recursive function findMinCoins to 
    find the minimum number of coins needed to make change for the given amount.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_COINS 100

int coinValues[MAX_NUM_COINS];
int minCoins[MAX_NUM_COINS];

// Function to find the minimum number of coins needed to make change for a given amount
int findMinCoins(int amount, int numCoins)
{
    // Base case: if amount is 0, then no coins are needed
    if (amount == 0)
        return 0;

    // Initialize the minimum number of coins needed to a large value
    int min = amount + 1;

    // Try using each coin as the last coin in the change
    for (int i = 0; i < numCoins; i++)
    {
        // Skip this coin if it is larger than the amount we are trying to make change for
        if (coinValues[i] > amount)
            continue;

        // Find the minimum number of coins needed to make change for the remaining amount
        int numCoinsForRemainingAmount = findMinCoins(amount - coinValues[i], numCoins);

        // If using this coin as the last coin in the change results in a smaller number of coins,
        // update the minimum number of coins needed
        if (numCoinsForRemainingAmount + 1 < min)
            min = numCoinsForRemainingAmount + 1;
    }

    return min;
}

int main(void)
{
    // Read the number of coins from the user
    int numCoins;
    printf("Enter the number of coins: ");
    scanf("%d", &numCoins);

    // Read the coin values from the user
    for (int i = 0; i < numCoins; i++)
    {
        printf("Enter the value of coin %d: ", i + 1);
        scanf("%d", &coinValues[i]);
    }

    // Read the amount for which we are trying to make change
    int amount;
    printf("Enter the amount for which you want to make change: ");
    scanf("%d", &amount);

    // Find the minimum number of coins needed to make change
    int min = findMinCoins(amount, numCoins);

    // Print the result
    printf("Minimum number of coins needed to make change for %d: %d\n", amount, min);

    return 0;
}
