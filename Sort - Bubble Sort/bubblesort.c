#include <stdio.h>
#include <stdbool.h>

void doSwap(char *xp, char *yp)
{
    int t = *xp;
    *xp = *yp;
    *yp = t;
}

void doSort(char arr[], int n)
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

void printArray(char arr[], int szArr)
{
    int i;
    for (i = 0; i < szArr; i++)
        printf("%c ", arr[i]);
    printf("\n");
}

int main()
{
    char arr[] = "ThisIsBubbleSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
