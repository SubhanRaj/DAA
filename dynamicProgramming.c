// Implementation an application of Dynamic Programming in C language
// This program uses dynamic programming to solve the Fibonacci sequence in C

#include <stdio.h>
#include <string.h>

#define MAX_N 50 // maximum number of terms in the Fibonacci sequence

int F[MAX_N + 1]; // array to store computed values of the Fibonacci sequence

// Calculate the nth term of the Fibonacci sequence using dynamic programming
int fibonacci(int n)
{
    if (n <= 1)
        return n; // base case for n = 0 or n = 1
    if (F[n] != -1)
        return F[n];                                   // check if value has been computed
    return F[n] = fibonacci(n - 1) + fibonacci(n - 2); // compute and store value
}

int main()
{
    printf("Implementation of an application of Dynamic Programming in C Language\n");
    printf("This program uses dynamic programming to solve the Fibonacci sequence in C:\n");

    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    // Initialize the F array with -1
    memset(F, -1, sizeof(F));

    // Check if input value for n is valid
    if (n < 0 || n > MAX_N)
    {
        printf("Error: Invalid value for n. n must be in the range [0, %d]\n", MAX_N);
        return 1;
    }

    printf("The first %d terms of the Fibonacci sequence are:\n", n);
    for (int i = 0; i < n; i++)
        printf("%d ", fibonacci(i));
    printf("\n");

    return 0;
}
