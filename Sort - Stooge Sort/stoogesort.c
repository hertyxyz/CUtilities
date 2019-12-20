#include <stdio.h>

void doSwap(char *xp, char *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

void doSort(char arr[], int l, int h)
{
    if (l >= h)
        return;
    if (arr[l] > arr[h])
        doSwap(&arr[l], &arr[h]);
    if (h - l + 1 > 2)
    {
        int t = (h - l + 1) / 3;
        doSort(arr, l, h - t);
        doSort(arr, l + t, h);
        doSort(arr, l, h - t);
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
    char arr[] = "ThisIsStoogeSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, 0, n - 1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
