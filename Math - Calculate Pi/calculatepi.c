#include "stdio.h"
#include "stdlib.h"

#define SCALE 100000
#define ARRINIT 2000

void pi_digits(int digits) {
    int carry = 0;
    int arr[digits + 1];
    for (int i = 0; i <= digits; ++i)
        arr[i] = ARRINIT;
    for (int i = digits; i > 0; i-= 14) {
        int sum = 0;
        for (int j = i; j > 0; --j) {
            sum = sum * j + SCALE * arr[j];
            arr[j] = sum % (j * 2 - 1);
            sum /= j * 2 - 1;
        }
        printf("%04d", carry + sum / SCALE);
        carry = sum % SCALE;
    }
}

int main(int argc, char** argv) {
    int n = argc == 2 ? atoi(argv[1]) : 100;
    pi_digits(n);

    return 0;
}
