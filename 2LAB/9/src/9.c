#include "../include/9.h"
#include <limits.h>
#include <math.h>
#include <stdarg.h>

kOpt IsFinite(double decimal, int base) {
    if (base == 10) return OPT_SUCCESS;
    double count_of_numbers = log(INT_MAX) / log(base) + 1;
    int i = 0;
    double fraction = decimal - (int) decimal;
    while (fraction != 0) {
        fraction *= base;
        if (fraction >= 1) {
            fraction -= (int)fraction;
        }
        i++;
        if (i > count_of_numbers) {
            return OPT_FAIL;
        }
    }
    return OPT_SUCCESS;
}

void CheckFiniteHandle(FiniteAnswer *results, int base, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        results[i].number = num;
        results[i].status = OPT_FAIL;
        if (IsFinite(num, base) == OPT_SUCCESS) {
            results[i].status = OPT_SUCCESS;
        }
    }

    va_end(args);
}
