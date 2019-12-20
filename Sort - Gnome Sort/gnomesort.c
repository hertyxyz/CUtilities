#include <stdio.h>

void doSwap(char *xp, char *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

void doSort(char arr[], int n)
{
    int index = 0;
    while (index < n)
    {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            doSwap(&arr[index], &arr[index - 1]);
            index--;
        }
    }
    return;
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
    char arr[] = "ThisIsGnomeSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
