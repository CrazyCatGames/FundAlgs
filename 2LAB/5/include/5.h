#ifndef INC_5_5_H
#define INC_5_5_H

#include <stdbool.h>
#include <stdio.h>

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
kOpt ToRoman(int number, char** r_value);
void Fibonacci(unsigned int result[2], unsigned int number);
void Zeckendorf(int* result_size, unsigned int number, unsigned int result[number][2]);
kOpt FromDecimal(long long decimal_number, int base, int flag,  char** result);
kOpt ToDecimal(char* number_str, int base, long long *dec_number, int flag);
bool is_lower(char* str, int size);
bool is_upper(char* str, int size);
int overfprintf(FILE * stream, char * format, ...);
int oversprintf(char* buf, char * format, ...);

#endif
