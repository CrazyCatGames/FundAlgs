#include "include/2.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	Vector *max = NULL;
	Vector vector1, vector2, vector3, vector4;
	int dimension = 3;
	vector1.coord = (double *) malloc(dimension * sizeof(double));
	if (!vector1.coord){
		fprintf(stderr, "Error malloc memory.\n");
		return 1;
	}
	vector1.coord[0] = 1.0;
	vector1.coord[1] = 2.0;
	vector1.coord[2] = -3.0;

	vector2.coord = (double *) malloc(dimension * sizeof(double));
	if (!vector2.coord){
		fprintf(stderr, "Error malloc memory.\n");
		free(vector1.coord);
		return 1;
	}
	vector2.coord[0] = 24.0;
	vector2.coord[1] = 0.0;
	vector2.coord[2] = 1.0;

	vector3.coord = (double *) malloc(dimension * sizeof(double));
	if (!vector3.coord){
		fprintf(stderr, "Error malloc memory.\n");
		free(vector1.coord);
		free(vector2.coord);
		return 1;
	}
	vector3.coord[0] = 0.0;
	vector3.coord[1] = 0.0;
	vector3.coord[2] = 0.0;

	vector4.coord = (double *) malloc(dimension * sizeof(double));
	if (!vector4.coord){
		fprintf(stderr, "Error malloc memory.\n");
		free(vector1.coord);
		free(vector2.coord);
		free(vector3.coord);
		return 1;
	}
	vector4.coord[0] = 24.0;
	vector4.coord[1] = 3.0;
	vector4.coord[2] = 3.0;

	char flag = 0;
	int count = 4;
	int size;
	int p = 5;

	kOpt status = GetMaxLenVector(&max, &size, NormMatrix, dimension, p, count, vector1, vector2, vector3, vector4);
	if (status == OPT_ERROR_INPUT) {
		fprintf(stderr, "Invalid parameter.\n");
	} else if (status == OPT_ERROR_MEMORY) {
		fprintf(stderr, "Error malloc memory.\n");
	} else if (status == OPT_ERROR) {
		fprintf(stderr, "Error. Value become NAN or INF.\n");
	} else {
		flag = 1;
	}

	if (flag) {
		for (int i = 0; i < size; i++) {
			PrintVector(&max[i], dimension);
		}
	}

	free(max);
	free(vector1.coord);
	free(vector2.coord);
	free(vector3.coord);
	free(vector4.coord);
	return 0;
}
