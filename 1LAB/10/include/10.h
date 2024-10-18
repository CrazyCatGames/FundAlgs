#ifndef LAB10_H
#define LAB10_H

int IsGreater(const char *num1, const char *num2, int base);
long long ConvertToDecimal(const char *num, int from_base, int *overflow);
char *ConvertFromDecimal(long long value, int to_base);
char *ConvertBase(const char *num, int from_base, int to_base, int *error);
int IsValidNumber(const char *num, int base);

#endif