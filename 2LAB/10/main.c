#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "include/10.h"

int main() {
  double* coefs_g = NULL;
  int size_coefs;
  int degree = 5;
  double epsilon = 1e-6;

  switch (SolveCoefs(1.0, &coefs_g, &size_coefs, degree, epsilon, -100.0, 7.0, -2.0, 0.0, 51.0, 1.0)) {
  case OPT_SUCCESS:
    printf("f(x) = ");
    for (int i = 0; i < degree + 1; i++) {
      if (i == 0) {
        printf("%f", coefs_g[i]);
      } else {
        printf(" + %f*(x - 1)^%d", coefs_g[i], i);
      }
    }
    printf("\n");
    break;
  case OPT_ERROR:
    fprintf(stderr, "Invalid parameter.\n");
    break;
  case OPT_ALLOC:
    fprintf(stderr, "Error malloc memory\n");
    break;
  }

  free(coefs_g);
  return 0;
}
