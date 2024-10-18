#ifndef LAB3_H
#define LAB3_H

typedef enum kOpts { OPT_SUCCESS, OPT_SUCCESS_FAIL, OPT_ERROR, OPT_ERROR_STR, OPT_SUCCESS_COMPLEX, OPT_ERROR_A } kOpts;

typedef struct {
    double a;
    double b;
    double c;
    double root1_real;
    double root1_imag;
    double root2_real;
    double root2_imag;
    kOpts opt;
} QuadraticSolution;

kOpts SolveQuadratic(double epsilon, double a, double b, double c, double* root1_real, double* root1_imag,
                     double* root2_real, double* root2_imag);
kOpts CheckMultiples(int a, int b);
kOpts CheckTriangle(double epsilon, double a, double b, double c);
double MyStrtod(const char* str, char** end);
int MyStrtoi(const char* str, char** end);
kOpts HandleQuadratic(char* argv[], QuadraticSolution solutions[], int* num_solutions);
kOpts HandleMultiples(char* argv[], int* a, int* b);
kOpts HandleTriangle(char* argv[], double* a, double* b, double* c);
int CheckFlag(const char* kflag, char* valid_flag);

#endif