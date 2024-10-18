#include "../include/4.h"
#include <stdarg.h>
#include <stdlib.h>

void getDigits(long long num, int base, int *digits, int *size) {
    *size = 0;
    if (num == 0) {
        digits[(*size)++] = 0;
        return;
    }
    while (num > 0) {
        digits[(*size)++] = num % base;
        num /= base;
    }

    for (int i = 0; i < *size / 2; i++) {
        int temp = digits[i];
        digits[i] = digits[*size - i - 1];
        digits[*size - i - 1] = temp;
    }
}

long long digitsToNumber(int *digits, int size, int base) {
    long long num = 0;
    for (int i = 0; i < size; i++) {
        num = num * base + digits[i];
    }
    return num;
}

kOpt isKaprekar(long long num, int base) {
    if (num == 1){
        return OPT_SUCCESS;
    }

    long long square = num * num;
    int digits[64];
    int size;
    getDigits(square, base, digits, &size);

    for (int split = 1; split < size; split++) {
        int leftSize = split;
        int rightSize = size - split;

        int leftDigits[32];
        int rightDigits[32];

        for (int i = 0; i < leftSize; i++) {
            leftDigits[i] = digits[i];
        }
        for (int i = 0; i < rightSize; i++) {
            rightDigits[i] = digits[split + i];
        }

        long long left = digitsToNumber(leftDigits, leftSize, base);
        long long right = digitsToNumber(rightDigits, rightSize, base);

        if (right == 0) continue;

        if (left + right == num) {
            return OPT_SUCCESS;
        }
    }

    return OPT_FAIL;
}

kOpt FindKaprekar(KaprekarResult *results, int base, int count, ...) {
    if (base < 2 || base > 36) {
        return OPT_ERROR;
    }

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        const char *numStr = va_arg(args, const char *);

        char *endptr;
        long long num = strtoll(numStr, &endptr, base);

        if (endptr == numStr || *endptr != '\0') {
            results[i].result = OPT_INVALID_FORMAT;
        } else if (num < 0) {
            results[i].result = OPT_INVALID_FORMAT;
        } else if (num == LLONG_MAX){
            results[i].result = OPT_OVERFLOW;
        }else   {
            results[i].result = isKaprekar(num, base);
        }

        results[i].input = numStr;
    }

    va_end(args);
    return OPT_SUCCESS;
}
