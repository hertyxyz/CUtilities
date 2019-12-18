#include <stdio.h>

char getMax(char arr[], int n)
{
    char mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(char arr[], int n, int exp)
{
    int output[n];
    int i, c[10] = {0};
    for (i = 0; i < n; i++)
        c[ (arr[i]/exp)%10 ]++;
    for (i = 1; i < 10; i++)
        c[i] += c[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[c[ (arr[i]/exp)%10 ] - 1] = arr[i];
        c[ (arr[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void doSort(char arr[], int n)
{
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
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
    char arr[] = "ThisIsRadixSort";
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Unsorted array: \n");
    printArray(arr, n);
    doSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
