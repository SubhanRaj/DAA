// Implementation of Single - Source Shortest Path Algorithm(Bellman - Ford Algorithm) in C Language

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, k, u, v, w, source, cost[10][10], distance[10], pred[10];
    printf("***SINGLE SOURCE SHORTEST PATH ALGORITHM(BELLMAN-FORD ALGORITHM)***\n");
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the cost matrix: \n");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = 999;
        }
    printf("Enter the source node: ");
    scanf("%d", &source);
    for (i = 1; i <= n; i++) {
        distance[i] = cost[source][i];
        pred[i] = source;
    }
    distance[source] = 0;
    for (i = 1; i <= n - 1; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= n; k++) {
                if (distance[j] > distance[k] + cost[k][j]) {
                    distance[j] = distance[k] + cost[k][j];
                    pred[j] = k;
                }
            }
        }
    }
    for (i = 1; i <= n; i++) {
        if (i != source) {
            printf("\nThe shortest path from %d to %d is: ", source, i);
            printf("%d", i);
            j = i;
            do {
                j = pred[j];
                printf("<-%d", j);
            } while (j != source);
            printf("\nThe cost is: %d", distance[i]);
        }
    }
    return 0;
}
