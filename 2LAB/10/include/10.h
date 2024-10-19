#ifndef LAB10_H
#define LAB10_H

typedef enum {
  OPT_SUCCESS,
  OPT_ERROR,
  OPT_ALLOC
} kOpt;

void Derivate(int degree, double *coeffs);
kOpt SolvePolynomial(double* res, double point, int degree, const double *coefs);
kOpt SolveCoefs(double a, double** coefs_g, int* size_coefs, int degree, double epsilon, ...);

#endif
