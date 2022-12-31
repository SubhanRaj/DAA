// Implementation of the Native String Matching Algorithm in C Language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char text[100], pattern[100];
    int i, j, n, m, flag = 0;
    printf("***NATIVE STRING MATCHING ALGORITHM***\n");
    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter the pattern: ");
    scanf("%s", pattern);
    n = strlen(text);
    m = strlen(pattern);
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) {
            printf("The pattern is found at position %d in the text.\n", i + 1);
            flag = 1;
        }
    }
    if (flag == 0)
        printf("The pattern is not found in the text.\n");
    return 0;
}
