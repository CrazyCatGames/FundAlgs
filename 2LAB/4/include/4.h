#ifndef INC_4_4_H
#define INC_4_4_H

typedef enum {
    OPT_SUCCESS,
    OPT_FAIL,
    OPT_ERROR,
    OPT_INVALID_FORMAT
} kOpt;

typedef struct {
    const char *input;
    kOpt result;
} KaprekarResult;

int countDigits(long long num, int base);
void getDigits(long long num, int base, int *digits, int *size);
kOpt isKaprekar(long long num, int base);
kOpt FindKaprekar(KaprekarResult *results, int base, int count, ...);

#endif