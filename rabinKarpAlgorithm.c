// Implementation of the Rabin-Karp String Matching Algorithm in C language

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

/*
 * Calculates the hash value for a given pattern and a given
 * length using the rolling hash technique.
 */
long long calculate_hash(char *pattern, int m, int prime)
{
    long long hash = 0;
    for (int i = 0; i < m; i++)
    {
        hash = (hash * 10 + pattern[i]) % prime;
    }
    return hash;
}

/*
 * Function to search for a pattern in a given text using the
 * Rabin-Karp algorithm.
 */
void search(char *text, char *pattern, int prime)
{
    int n = strlen(text);
    int m = strlen(pattern);

    // Calculate h as 10 ^ (m - 1) modulo prime
    long long h = 1;
    for (int i = 0; i < m - 1; i++)
    {
        h = (h * 10) % prime;
    }

    // Calculate the hash value for the pattern and the first window of text
    long long p = calculate_hash(pattern, m, prime);
    long long t = calculate_hash(text, m, prime);

    for (int i = 0; i <= n - m; i++)
    {
        // Check if the pattern and the text match
        if (p == t)
        {
            int j;
            for (j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    break;
                }
            }
            if (j == m)
            {
                printf("Pattern found at index %d\n", i);
            }
        }
        // Calculate the hash value for the next window of text
        if (i < n - m)
        {
            t = (10 * (t - text[i] * h) + text[i + m]) % prime;
            if (t < 0)
            {
                t = (t + prime);
            }
        }
    }
}

int main()
{
    char text[MAX], pattern[MAX];
    int prime = 101; // A prime number
    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);
    search(text, pattern, prime);
    return 0;
}
