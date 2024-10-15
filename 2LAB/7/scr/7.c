#include "../include/7.h"
#include <math.h>

double Equation(double x) {
    return x * x * x - 8;
}

kOpt Bisection(double (*func)(double), double a, double b, double epsilon, double *root) {
    if (func(a) * func(b) >= 0) {
        return OPT_FAIL;
    }

    while ((b - a) >= epsilon) {
        *root = (a + b) / 2;

        if (fabs(func(*root)) < epsilon) {
            break;
        }

        if (func(*root) * func(a) < 0) {
            b = *root;
        } else {
            a = *root;
        }
    }

    return OPT_SUCCESS;
}