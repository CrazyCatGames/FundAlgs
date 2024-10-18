#include "../include/3.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kOpts SolveQuadratic(double epsilon, double a, double b, double c, double* root1_real, double* root1_imag,
                     double* root2_real, double* root2_imag) {
	if (a == 0) {
		return OPT_ERROR_A;
	}

	double disc = b * b - 4 * a * c;

	if (fabs(disc) < epsilon) {
		disc = 0;
	}

	if (disc > 0) {
		double sqrt_disc = sqrt(disc);
		*root1_real = (-b + sqrt_disc) / (2 * a);
		*root2_real = (-b - sqrt_disc) / (2 * a);
		return OPT_SUCCESS;
	} else if (disc == 0) {
		*root1_real = *root2_real = -b / (2 * a);
		return OPT_SUCCESS;
	} else {
		double sqrt_disc = sqrt(-disc);
		*root1_real = *root2_real = -b / (2 * a);
		*root1_imag = sqrt_disc / (2 * a);
		*root2_imag = -sqrt_disc / (2 * a);
		return OPT_SUCCESS_COMPLEX;
	}
}

kOpts CheckMultiples(int a, int b) {
	if (b == 0) {
		return OPT_ERROR;
	}

	if (a % b == 0) {
		return OPT_SUCCESS;
	} else {
		return OPT_SUCCESS_FAIL;
	}
}

kOpts CheckTriangle(double epsilon, double a, double b, double c) {
	double sides[3] = {a, b, c};
	if (a < 0 || b < 0 || c < 0) {
		return OPT_ERROR;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			if (sides[i] > sides[j]) {
				double temp = sides[i];
				sides[i] = sides[j];
				sides[j] = temp;
			}
		}
	}

	if (fabs((sides[0] * sides[0] + sides[1] * sides[1]) - sides[2] * sides[2]) < epsilon) {
		return OPT_SUCCESS;
	} else {
		return OPT_SUCCESS_FAIL;
	}
}

int CheckFlag(const char* kflag, char* valid_flag) {
	return (kflag[0] == '-' || kflag[0] == '/') && strcmp(&kflag[1], valid_flag) == 0;
}

double MyStrtod(const char* str, char** end) {
	while (isspace((unsigned char)*str)) {
		str++;
	}

	int sign = 1;
	if (*str == '-') {
		sign = -1;
		str++;
	} else if (*str == '+') {
		str++;
	}

	double integer_part = 0.0;
	while (isdigit((unsigned char)*str)) {
		integer_part = integer_part * 10 + (*str - '0');
		str++;
	}

	double fraction_part = 0.0;
	if (*str == '.') {
		str++;
		double divisor = 10.0;
		while (isdigit((unsigned char)*str)) {
			fraction_part += (*str - '0') / divisor;
			divisor *= 10;
			str++;
		}
	}

	double result = sign * (integer_part + fraction_part);

	if (end) {
		*end = (char*)str;
	}

	return result;
}

int MyStrtoi(const char* str, char** end) {
	while (isspace((unsigned char)*str)) {
		str++;  // skip spaces
	}

	int sign = 1;
	if (*str == '-') {
		sign = -1;
		str++;
	} else if (*str == '+') {
		str++;
	}

	int result = 0;
	while (isdigit((unsigned char)*str)) {
		result = result * 10 + (*str - '0');
		str++;
	}

	if (end) {
		*end = (char*)str;
	}

	return sign * result;
}

kOpts HandleQuadratic(char* argv[], QuadraticSolution solutions[], int* num_solutions) {
    char *end1, *end2, *end3, *end4;
    double epsilon = MyStrtod(argv[2], &end1);
    double coeffs[3] = { MyStrtod(argv[3], &end2), MyStrtod(argv[4], &end3), MyStrtod(argv[5], &end4) };

    if (*end1 != '\0' || *end2 != '\0' || *end3 != '\0' || *end4 != '\0') {
        return OPT_ERROR_STR;
    }

    double permutations[6][3] = {
        { coeffs[0], coeffs[1], coeffs[2] },
        { coeffs[0], coeffs[2], coeffs[1] },
        { coeffs[1], coeffs[0], coeffs[2] },
        { coeffs[1], coeffs[2], coeffs[0] },
        { coeffs[2], coeffs[0], coeffs[1] },
        { coeffs[2], coeffs[1], coeffs[0] }
    };

    *num_solutions = 0;
    for (int i = 0; i < 6; i++) {
        double a = permutations[i][0];
        double b = permutations[i][1];
        double c = permutations[i][2];
        
        int is_duplicate = 0;
        for (int j = 0; j < *num_solutions; j++) {
            if (a == solutions[j].a &&
                b == solutions[j].b &&
                c == solutions[j].c) {
                is_duplicate = 1;
                break;
            }
        }
        
        if (!is_duplicate) {
            QuadraticSolution sol;
            sol.a = a;
            sol.b = b;
            sol.c = c;
            sol.opt = SolveQuadratic(epsilon, sol.a, sol.b, sol.c, &sol.root1_real, &sol.root1_imag, &sol.root2_real, &sol.root2_imag);
            solutions[*num_solutions] = sol;
            (*num_solutions)++;
        }
    }
	return OPT_SUCCESS;
}

kOpts HandleMultiples(char* argv[], int* a, int* b) {
	char *end1, *end2;
	*a = MyStrtoi(argv[2], &end1);
	*b = MyStrtoi(argv[3], &end2);
	if (*end1 != '\0' || *end2 != '\0') {
		return OPT_ERROR_STR;
	}

	return CheckMultiples(*a, *b);
}

kOpts HandleTriangle(char* argv[], double* a, double* b, double* c) {
	char *end1, *end2, *end3, *end4;
	double epsilon = MyStrtod(argv[2], &end1);
	*a = MyStrtod(argv[3], &end2);
	*b = MyStrtod(argv[4], &end3);
	*c = MyStrtod(argv[5], &end4);
	if (*end1 != '\0' || *end2 != '\0' || *end3 != '\0' || *end4 != '\0') {
		return OPT_ERROR_STR;
	}

	return CheckTriangle(epsilon, *a, *b, *c);
}