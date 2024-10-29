#ifndef INC_2_2_H
#define INC_2_2_H

#define EPS 1e-6

typedef enum kOpt{
	OPT_SUCCESS,
	OPT_ERROR,
	OPT_ERROR_MEMORY,
	OPT_ERROR_INPUT
} kOpt;

typedef struct Vector {
	double* coord;
} Vector;

void PrintVector(Vector* arr, int size);
kOpt GetMaxLenVector(Vector** max_vectors, int* size, kOpt norm(double* res, Vector* vect, int n, int p), int dimension, int p, int count,...);
kOpt NormMatrix(double* res, Vector* vect, int n, int p);
kOpt NormMax(double* res, Vector* vect, int n, int p);
kOpt NormP(double* res, Vector* vect, int n, int p);

#endif
