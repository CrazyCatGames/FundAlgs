#include "../include/10.h"
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

void Derivate(int degree, double coeffs[]) {
  for (int i = 0; i < degree; i++) {
    coeffs[i] = coeffs[i + 1] * (i + 1);
  }
}

kOpt SolvePolynomial(double* res, double point, int degree, double coefs[]) {
  *res = 0;
  int cur_degree = 1;
  for (int i = 0; i < degree + 1; i++) {
    *res += coefs[i] * cur_degree;
    cur_degree *= point;
  }
  return OPT_SUCCESS;
}

kOpt SolveCoefs(double a, double** coefs_g, int* size_coefs, int degree, double epsilon, ...) {
  if (degree < 0) {
    return OPT_ERROR;
  }
    
  va_list ptr;
  va_start(ptr, epsilon);
  *coefs_g = (double*)malloc((degree + 1) * sizeof(double));
  if (*coefs_g == NULL) {
    return OPT_ALLOC;
  }
    
  double coefs[degree + 1];
  for (int i = 0; i < degree + 1; i++) {
    coefs[i] = va_arg(ptr, double);
  }
  va_end(ptr);
    
  double factorial_tmp = 1;
  for (int i = 0; i < degree + 1; i++) {
    double coefficient_g;
    SolvePolynomial(&coefficient_g, a, degree - i, coefs);
        
    if (fabs(coefficient_g) < epsilon) {
      coefficient_g = 0.0;
    }
        
    (*coefs_g)[i] = coefficient_g;
        
    if (i > 1) {
      factorial_tmp *= i;
      (*coefs_g)[i] /= factorial_tmp;
    }
        
    Derivate(degree - i, coefs);
  }
    
  *size_coefs = degree + 1;
  return OPT_SUCCESS;
}