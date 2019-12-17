#include <stdio.h>

void doSwap(int *xp, int *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

void doSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n-1; i++)
    {
        swapped = false;
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                doSwap(&arr[j], &arr[j+1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
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
