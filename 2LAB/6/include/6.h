#ifndef INC_6_6_H
#define INC_6_6_H

#include <stdbool.h>
#include <stdio.h>

#define STR_SIZE 1024

typedef enum optRealloc {
	OPT_REALLOC_SUCCESS,
	OPT_REALLOC_FAIL
} optRealloc;

typedef enum kOpt {
	OPT_SUCCESS,
	OPT_INVALID_PARAMETER,
	OPT_ERROR_ALLOC
} kOpt;

optRealloc MyRealloc(void** var, int size);
bool is_lower(const char* str, int size);
bool is_upper(const char* str, int size);
bool is_digit_str(const char* str, int size);
kOpt FromRoman(const char* number_str, int* num);
kOpt FromZeckendorf(const char* number_z, unsigned int* number);
kOpt ToDecimal(char* number_str, int base, int* dec_number, int flag);
int overfscanf(FILE * stream, const char * format, ...);
int oversscanf(char * buf, const char * format, ...);

#endif
