#ifndef LAB7_H
#define LAB7_H

typedef enum kOpt{
    OPT_SUCCESS,
    OPT_FAIL,
} kOpt;
double Equation(double x);
kOpt Bisection(double (*func)(double), double a, double b, double epsilon, double *root);

#endif
