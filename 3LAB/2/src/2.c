#include "../include/2.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void PrintVector(Vector *arr, int size) {
	printf("<");
	for (int i = 0; i < size; i++) {
		printf("%.3lf", arr->coord[i]);
		if (i != size - 1) {
			printf(", ");
		}
	}
	printf(">");
	printf("\n");
}

kOpt NormMax(double *res, Vector *vect, int n, int p) {
	if (!vect || !res) return OPT_ERROR_INPUT;

	*res = 0.0;
	for (int i = 0; i < n; i++) {
		*res = fmax(*res, fabs(vect->coord[i]));
	}

	return OPT_SUCCESS;
}

kOpt NormP(double *res, Vector *vect, int n, int p) {
	if (!vect || !res) return OPT_ERROR_INPUT;
	*res = 0.0;
	if (p < 1) return OPT_ERROR_INPUT;

	for (int i = 0; i < n; i++) {
		*res += pow(fabs(vect->coord[i]), p);
	}

	*res = pow(*res, 1.0 / p);
	return OPT_SUCCESS;
}

kOpt NormMatrix(double *res, Vector *vect, int n, int p) {
	if (!vect || !res) return OPT_ERROR_INPUT;

	double A[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = (j == i);
		}
	}

	*res = 0.0;
	for (int i = 0; i < n; i++) {
		double tmp = 0.0;
		for (int j = 0; j < n; j++){
			tmp += A[i][j] * vect->coord[j];
		}
		*res += tmp * vect->coord[i];
	}

	*res = sqrt(*res);
	return OPT_SUCCESS;
}

kOpt GetMaxLenVector(Vector **max_vectors, int *size, kOpt norm(double *res, Vector *vect, int n, int p), int dimension, int p, int count, ...) {
	if (count < 1 || dimension < 1) return OPT_ERROR_INPUT;

	va_list ptr;
	va_start(ptr, count);
	Vector vectors[count];
	for (int i = 0; i < count; i++){
		vectors[i] = va_arg(ptr, Vector);
	}
	va_end(ptr);

	char max_vector_mask[count];
	for (int i = 0; i < count; i++){
		max_vector_mask[i] = '\0';
	}

	double max = 0.0;
	int count_max_vectors = 0;
	for (int i = 0; i < count; ++i) {
		double norm_value;
		kOpt status_norm = norm(&norm_value, &vectors[i], dimension, p);
		if (status_norm == OPT_ERROR_INPUT) return OPT_ERROR_INPUT;
		if (isinf(norm_value) || isnan(norm_value)) return OPT_ERROR;

		if (norm_value - max > EPS) {
			max = norm_value;
			for (int j = 0; j < count; j++){
				max_vector_mask[j] = '\0';
			}

			max_vector_mask[i] = 1;
			count_max_vectors = 1;
		} else if (fabs(norm_value - max) < EPS) {
			max_vector_mask[i] = 1;
			count_max_vectors++;
		}
	}

	*size = count_max_vectors;
	*max_vectors = malloc(sizeof(Vector) * count_max_vectors);
	if (!*max_vectors) return OPT_ERROR_MEMORY;

	int index = 0;
	for (int i = 0; i < count; i++) {
		if (max_vector_mask[i]) {
			(*max_vectors)[index++] = vectors[i];
		}
	}

	return OPT_SUCCESS;
}