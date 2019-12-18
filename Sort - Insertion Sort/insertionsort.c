#include <stdio.h>
#include <math.h>

void doSort(char arr[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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
    char arr[] = "ThisIsInsertionSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
