#include <stdio.h>
#include <stdlib.h>
#include "include/10.h"

int main() {
  double* coefs_g = NULL;
  int size_coefs;
  int degree = 5;
  double epsilon = 1e-6;
  double a = 1.0;

  switch (SolveCoefs(a, &coefs_g, &size_coefs, degree, epsilon, -50.0, 7.0, -2.0, 0.0, 51.0, 1.0)) {
  case OPT_SUCCESS:
    printf("f(x) = ");
    for (int i = 0; i < degree + 1; i++) {
      if (i == 0) {
        printf("%f", coefs_g[i]);
      } else {
        printf(" + %.2f*(x - %.2f)^%d", coefs_g[i], a , i);
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
