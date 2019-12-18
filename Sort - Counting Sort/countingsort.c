#include <stdio.h>
#include <string.h>

void doSort(char arr[], int range)
{
    char out[strlen(arr)];
    int count[range + 1], i;
    memset(count, 0, sizeof(count));
    for (i = 0; arr[i]; i++)
        count[arr[i]]++;
    for (i = 1; i <= range; i++)
        count[i] += count[i-1];
    for (i = 0; arr[i]; i++)
    {
        out[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (i = 0; arr[i]; i++)
        arr[i] = out[i];
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
    char arr[] = "ThisIsCountingSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, 255);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
