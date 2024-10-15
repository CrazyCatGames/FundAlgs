#include <stdlib.h>
#include <stdio.h>

#include "include/2.h"

int main(int argc, char *argv[]) {
	double result_geom;
	double result_pow;

	switch (GeomMean(&result_geom, 9, 2.0, 3.0, 4.0, 5.0, 3.4, 2.4, 1.5, 0.5, 7)) {
		case OPT_SUCCESS:
			printf("Result = %.80f\n", result_geom);
			break;
		case OPT_ERROR_OVERFLOW:
			printf("Overflow detected\n");
			break;
		case OPT_ERROR_INVALID:
			printf("Invalid parameter detected\n");
			break;
		case OPT_ERROR_NAN:
			printf("Result becomes a NaN\n");
			break;
		default:
			printf("Unknown error.\n");
	}

	printf("\n");
	printf("Enter base: \n");
	char *num_str = read_input();
	if (num_str == NULL) {
		fprintf(stderr, "Memory allocation failed for base.\n");
		return 1;
	}

	printf("Enter power: \n");
	char *power_str = read_input();
	if (power_str == NULL) {
		fprintf(stderr, "Memory allocation failed for power.\n");
		free(num_str);
		return 1;
	}

	char *end1, *end2;
	double num = MyStrtod(num_str, &end1);
	int power = MyStrtoi(power_str, &end2);

	if (*end1 != '\0' || *end2 != '\0') {
		fprintf(stderr, "Incorrect values.\n");
		free(num_str);
		free(power_str);
		return 1;
	}

	switch (FastPow(&result_pow, num, power)) {
		case OPT_SUCCESS:
			printf("Result = %.80f\n", result_pow);
			break;
		case OPT_ERROR_OVERFLOW:
			printf("Overflow detected\n");
			break;
		case OPT_ERROR_NAN:
			printf("Result becomes a NaN\n");
			break;
		default:
			printf("Unknown error.\n");
	}

	free(num_str);
	free(power_str);

	return 0;
}