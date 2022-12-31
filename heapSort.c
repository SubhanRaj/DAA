// Implementation of Heap Sort Algorithm in C Language

#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort

void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Driver code

int main()
{
    int n;
    printf("***HEAP SORT***\n");
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int choice;
    printf("Enter 1 for assending order and 2 for dessending order: ");
    scanf("%d", &choice);
    heapSort(arr, n);
    if (choice == 1) {
        printf("Sorted array in assending order: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
    }
    else if (choice == 2) {
        printf("Sorted array in dessending order: ");
        for (int i = n - 1; i >= 0; i--)
            printf("%d ", arr[i]);
    }
    else
        printf("Invalid choice");
    return 0;
}





