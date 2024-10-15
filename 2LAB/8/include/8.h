#ifndef LAB8_H
#define LAB8_H

#include <stdlib.h>

typedef enum kOpt { OPT_SUCCESS, OPT_ERROR_MEMORY, OPT_ERROR_NUMBER, OPT_ERROR_BASE } kOpt;

kOpt addInColumn(const char *num1, const char *num2, int base, char **result, size_t *result_size);
kOpt CheckDigit(int *digit, unsigned int len, int i, const char *num, int base);
void removeLeadingZeros(char *str);
kOpt sumNumbersInBase(int base, char **result, size_t *result_size, int count, ...);
unsigned int MyStrlen(const char *str);

#endif
