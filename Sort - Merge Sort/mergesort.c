#include <stdlib.h>
#include <stdio.h>

void doMerge(char arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    char L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + j + 1];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++ ;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void doSort(char arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        doSort(arr, l, m);
        doSort(arr, m+1, r);
        doMerge(arr, l, m, r);
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
    char arr[] = "ThisIsMergeSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, 0, n - 1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
