#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int MyStrtoi(const char *str, char **end) {
    while (isspace((unsigned char)*str)) {
        str++;
    }

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    int result = 0;
    while (isdigit((unsigned char)*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    if (end) {
        *end = (char *)str; 
    }

    return sign * result;
}

void FindAndSwap(int* arr, int size) {
    int index_of_min = 0;
    int index_of_max = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[index_of_min]) {
            index_of_min = i;
        }
        if (arr[i] > arr[index_of_max]) {
            index_of_max = i;
            }
    }

    int temp = arr[index_of_min];
    arr[index_of_min] = arr[index_of_max];
    arr[index_of_max] = temp;
}

void PrintArray(const int* karr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", karr[i]);
    }
    printf("\n\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error: Two numbers must be passed.\n");
        return 1;
    }
    char *end1, *end2;

    int a = MyStrtoi(argv[1], &end1);
    int b = MyStrtoi(argv[2], &end2);
    if (*end1 != '\0' || *end2 != '\0'){
        fprintf(stderr, "Number A and B must be integer.\n");
        return 1;
    }

    const int ksize = 15;
    int arr[15];

    // Initialize random number generator
    srand(time(NULL));

    for (int i = 0; i < ksize; i++) {
        arr[i] = rand() % (b - a + 1) + a;
    }

    printf("Source array:\n");
    PrintArray(arr, ksize);

    FindAndSwap(arr, ksize);

    printf("Array after swapping minimum and maximum elements:\n");
    PrintArray(arr, ksize);

    return 0;
}
