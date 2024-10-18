#include <stdio.h>

#include "../include/3.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("No flag provided.\n");
		return 1;
	}

	const char* kflag = argv[1];

	if (CheckFlag(kflag, "q") && argc == 6) {
		QuadraticSolution solutions[6];
		int num_solutions = 0;
		kOpts check = HandleQuadratic(argv, solutions, &num_solutions);

		if (check == OPT_ERROR_STR){
			fprintf(stderr, "Error: Invalid input for quadratic equation.\n");
			return 1;
		} 

		for (int i = 0; i < num_solutions; i++) {
			QuadraticSolution sol = solutions[i];

			printf("Equation: %.2lfx^2 + %.2lfx + %.2lf = 0\n", sol.a, sol.b, sol.c);
			
			switch (solutions[i].opt) {
				case OPT_SUCCESS:
					printf("Roots are: %.6f and %.6f\n\n", solutions[i].root1_real, solutions[i].root2_real);
					break;
				case OPT_SUCCESS_COMPLEX:
					printf("Complex roots: %.6lf + %.6lfi and %.6lf - %.6lfi\n\n", solutions[i].root1_real,
					       solutions[i].root1_imag, solutions[i].root2_real, solutions[i].root2_imag);
					break;
				case OPT_ERROR_A:
					fprintf(stderr, "Error: For these values, the equation is not a quadratic equation.\n\n");
					break;
				default:
					printf("Error: Unknown error.\n");
					break;
			}
		}
	} else if (CheckFlag(kflag, "m") && argc == 4) {
		int a, b;
		kOpts result = HandleMultiples(argv, &a, &b);

		switch (result) {
			case OPT_SUCCESS:
				printf("%d is a multiple of %d\n", a, b);
				break;
			case OPT_ERROR:
				printf("Error: Division by zero is not allowed.\n");
				break;
			case OPT_ERROR_STR:
				fprintf(stderr, "Error: Invalid input for multiples check.\n");
				break;
			case OPT_SUCCESS_FAIL:
				printf("%d is not a multiple of %d\n", a, b);
				break;
			default:
				printf("Error: Unknown error.\n");
				break;
		}
	} else if (CheckFlag(kflag, "t") && argc == 6) {
		double a, b, c;
		kOpts result = HandleTriangle(argv, &a, &b, &c);

		switch (result) {
			case OPT_SUCCESS:
				printf("A right-angled triangle exists with such sides.\n");
				break;
			case OPT_ERROR:
				printf("Sides must be positive lengths.\n");
				break;
			case OPT_ERROR_STR:
				fprintf(stderr, "Error: Invalid input for triangle check.\n");
				break;
			case OPT_SUCCESS_FAIL:
				printf("A right-angled triangle does not exist with such sides.\n");
				break;
			default:
				printf("Error: Unknown error.\n");
				break;
		}
	} else {
		fprintf(stderr, "Invalid flag or wrong number of arguments.\n");
		return 1;
	}

	return 0;
}
