#ifndef LAB1_H
#define LAB1_H

typedef enum kOpts { OPT_SUCCESS, OPT_FAIL, OPT_ERROR_OVERFLOW, OPT_ERROR_INVALID, OPT_ERROR_NAN } kOpts;

kOpts GeomMean(double* res, int count,...);
kOpts FastPow(double* res, double value, int degree);
int MyStrtoi(const char* str, char** end);
double MyStrtod(const char* str, char** end);
char *read_input();

#endif