// Implementation of Lienar Time Sorting Algorithm in C Language

#include <stdio.h>
#include <stdlib.h>

int linearTimeSort(int *arr, int n);

int linearTimeSort(int *arr, int n)
{
    int count[3] = {0, 0, 0};
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }
    int i = 0;
    while (count[0] > 0)
    {
        arr[i] = 0;
        i++;
        count[0]--;
    }
    while (count[1] > 0)
    {
        arr[i] = 1;
        i++;
        count[1]--;
    }
    while (count[2] > 0)
    {
        arr[i] = 2;
        i++;
        count[2]--;
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    linearTimeSort(arr, n);
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("");
}
