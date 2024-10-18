#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int FindClose(int* arr, int size, int target) {
    int closest = arr[0];
    int min_difference = abs(arr[0] - target);

    for (int i = 1; i < size; i++) {
        int difference = abs(arr[i] - target);
        if (difference == 0){
            return arr[i];
        }
        if (difference < min_difference) {
            min_difference = difference;
            closest = arr[i];
        }
    }
    return closest;
}

void PrintArray(int* arr, int size, int n, const char* karray_name) {
    printf("First %d elements of array %s:\n", n, karray_name);
    for (int i = 0; i < n && i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    if (argc != 1){
        printf("Error: There should be no arguments.\n");
        return 1;
    }

    srand(time(NULL));

    const int ksize_a = rand() % (10000 - 10 + 1) + 10;
    const int ksize_b = rand() % (10000 - 10 + 1) + 10;

    int* A = (int*)malloc(ksize_a * sizeof(int));
    int* B = (int*)malloc(ksize_b * sizeof(int));
    int* C = (int*)malloc(ksize_a * sizeof(int));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 0; i < ksize_a; i++) {
        A[i] = rand() % 2001 - 1000;
    }

    for (int i = 0; i < ksize_b; i++) {
        B[i] = rand() % 2001 - 1000;
    }

    for (int i = 0; i < ksize_a; i++) {
        int closest = FindClose(B, ksize_b, A[i]);
        C[i] = A[i] + closest;
    }

    PrintArray(A, ksize_a, 15, "A");
    PrintArray(B, ksize_b, 15, "B");
    PrintArray(C, ksize_a, 15, "C");

    free(A);
    free(B);
    free(C);

    return 0;
}
