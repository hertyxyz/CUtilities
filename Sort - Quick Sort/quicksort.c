#include <stdio.h>

void doSwap(char *xp, char *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

int partition(char arr[], int low, int high)
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

void doSort(char arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        doSort(arr, low, pi - 1);
        doSort(arr, pi + 1, high);
    }
}

void printArray(char arr[], int szArr)
{
    int i;
    for (i = 0; i < szArr; i++)
        printf("%c ", arr[i]);
    printf("\n");
}

int main()
{
    char arr[] = "ThisIsQuickSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, 0, n - 1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
