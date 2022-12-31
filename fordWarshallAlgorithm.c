// Implementation of Ford-Warshall All Pair Shortest Path Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int main()
{
    int n, i, j, k, a[MAX][MAX], d[MAX][MAX], u, v;
    printf("********** Ford-Warshall All Pair Shortest Path Algorithm **********\n");
    printf("Enter the number of vertices: \n");
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    printf("\nEnter the pair of vertices that the shortest path must pass through: \n");
    scanf("%d %d", &u, &v);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            d[i][j] = a[i][j];
            if (i == u && j == v)
            {
                d[i][j] = 0;
            }
            else if (i == v && j == u)
            {
                d[i][j] = 0;
            }
        }
    }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (k == u || k == v)
                {
                    if (d[i][k] + d[k][j] < d[i][j])
                    {
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }
    }

    printf("\nThe shortest path matrix is: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", d[i][j]);
        }
        printf("\n");
    }

    return 0;
}
