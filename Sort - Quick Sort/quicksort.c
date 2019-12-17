#include <stdio.h>

void doSwap(int *xp, int *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

int partition(int arr[], int low, int high)
{
    int j;
    int pivot = arr[high];
    int i = (low - 1);
    for (j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            doSwap(&arr[i], &arr[j]);
        }
    }
    doSwap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void doSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        doSort(arr, low, pi - 1);
        doSort(arr, pi + 1, high);
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
    doSort(arr, 0, n - 1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
