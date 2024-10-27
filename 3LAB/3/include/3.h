#ifndef INC_3_3_H
#define INC_3_3_H

#include <stdio.h>

#define EPS 1e-6

typedef enum kOpt{
	OPT_SUCCESS,
	OPT_ERROR_INPUT,
	OPT_ERROR_MEMORY
} kOpt;

typedef struct Employee{
	unsigned int id;
	char *name;
	char *surname;
	double salary;
} Employee;

kOpt ValidateInput(int argc, char **argv);
kOpt ValidateData(Employee data);
char *ReadString(FILE *file, int flag);
kOpt GetEmployee(FILE *file, Employee **data, int *size);
int CompareA(const void *a, const void *b);
int CompareB(const void *a, const void *b);

#endif
