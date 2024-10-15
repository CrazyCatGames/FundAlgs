#ifndef LAB9_H
#define LAB9_H

typedef enum kOpt{
    OPT_SUCCESS,
    OPT_FAIL
} kOpt;

typedef struct FiniteAnswer {
    double number;
    kOpt status;
} FiniteAnswer;

kOpt IsFinite(double decimal, int base);
void CheckFiniteHandle(FiniteAnswer *res, int base, int count, ...);

#endif
