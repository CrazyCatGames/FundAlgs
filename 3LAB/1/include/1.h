#ifndef INC_1_1_H
#define INC_1_1_H

#include <stdlib.h>

typedef enum kOpt{
	OPT_SUCCESS,
	OPT_ERROR,
	OPT_MEMORY,
} kOpt;

kOpt Convert(char **answer, int *size, int num, int power, size_t *size_res);
void PrintResult(const char *result, int size);
int Add(int a, int b);

#endif