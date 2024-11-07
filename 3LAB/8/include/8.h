#ifndef INC_8_8_H
#define INC_8_8_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum kOpt {
	OPT_SUCCESS,
	OPT_INPUT_ERROR,
	OPT_MEMORY_ERROR,
	OPT_OVERFLOW_ERROR,
	OPT_FILE_OPEN_ERROR,
	OPT_ZERO_ARGS
} kOpt;

typedef struct String {
	char *arr;
	size_t len, capacity;
} String;

typedef struct Term {
	int coef;
	int degree;
	struct Term *next;
} Term;

typedef struct Polynom {
	size_t size;
	Term *head;
} Polynom;

kOpt InitString(String *string);
kOpt DeleteString(String *string);
kOpt AddCharToString(String *str, char ch);

kOpt Div(Polynom *dividend, Polynom *divider, Polynom *quotient);
kOpt InitPolynom(Polynom *polynom);
kOpt InsertTerm(Polynom *polynom, int degree, int coef);
kOpt DestroyPolynom(Polynom *polynom);
kOpt CreatePolynom(Polynom *polynom, const char *expression);
kOpt Add(Polynom *polynom_1, Polynom *polynom_2);
kOpt Multiply(Polynom *polynom_1, Polynom *polynom_2, Polynom *res);
kOpt Eval(Polynom *polynom, double x, double *result);
kOpt Diff(Polynom *polynom, Polynom *res);
kOpt Cmps(Polynom *polynom_1, Polynom *polynom_2, Polynom *result);
kOpt Mod(Polynom *dividend, Polynom *divider, Polynom *res);
kOpt Sub(Polynom *polynom_1, Polynom *polynom_2);
kOpt PrintPolynom(Polynom *polynom);
kOpt GetExpression(Polynom *polynom_1, Polynom *polynom_2, FILE *input, int *count);

#endif
