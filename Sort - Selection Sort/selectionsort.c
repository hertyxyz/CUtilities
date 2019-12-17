#include <stdio.h>

void doSwap(int *xp, int *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

void doSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        doSwap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[], int szArr)
{
    int i;
    for (i = 0; i < szArr; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
