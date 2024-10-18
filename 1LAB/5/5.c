#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef enum kOpts { OPT_A, OPT_B, OPT_C, OPT_D } kOpts;

unsigned int DoubleFactorial(int n) {
    if (n <= 0){
        return 1;
    }
    unsigned int fact = 1;
    
    while (n > 0) {
        fact *= n;
        n -= 2;
    }
    
    return fact;
}

unsigned int Factorial(unsigned int n) {
    unsigned int fact = 1;

    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

void SumA(double x, double epsilon) {
    int n = 0;
    double summ = 0.0;
    double temp = 1.0;  // Start value (x^0)/(0!) = 1

    while (fabs(temp) > epsilon) {
        summ += temp;
        n++;
        temp *= x / n;
    }

    printf("The amount: %.10f\n", summ);
}

void SumB(double x, double epsilon) {
    int n = 0;
    double summ = 0.0;
    double temp = 1.0;  // Start value 1*(x^0)/((2*0)!) = 1

    while (fabs(temp) > epsilon) {
        summ += temp ;
        n++;
        temp = pow(-1, n) * pow(x, 2 * n) / (Factorial(2 * n));
    }

    printf("The amount: %.10f\n", summ);
}

void SumC(double x, double epsilon) {
    int n = 0;
    long double summ = 0.0;
    long double temp = 1.0;  // Start value ((3^0)*((0!)^3)*(x^0 ))/(3*0)! = 1
    long long factorial_3n = 1;
    long long factorial_n = 1;

    while (fabs(temp) > epsilon) {
        summ += temp;
        n++;

		if (isnan(summ)) {
            fprintf(stderr, "SumC: summ became NaN at iteration %d\n", n);
            return;
        }

        factorial_3n = Factorial(3 * n);
        factorial_n *= n;
        temp = pow(3, 3 * n) * pow(factorial_n, 3) * pow(x, 2 * n) / factorial_3n;
    }

    printf("The amount: %.10Lf\n", summ);
}

void SumD(double x, double epsilon) {
    int n = 1;
    double summ = 0.0;
    long double temp = -x * x / 2;  // Start value n = 1
    long long double_factorial_even = 2;
    long long double_factorial_odd = 1;

    while (fabs(temp) > epsilon) {
        summ += temp;
        n++;

		if (isnan(summ)) {
            fprintf(stderr, "SumD: summ became NaN at iteration %d\n", n);
            return;
        }

        double_factorial_even = DoubleFactorial(2 * n);
        double_factorial_odd = DoubleFactorial(2 * n - 1);
        temp = pow(-1, n) * double_factorial_odd * pow(x, 2 * n) / double_factorial_even;
    }

    printf("The amount: %.10f\n", summ);
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

int CheckFlag(const char* kflag, char* valid_flag) {
	return (kflag[0] == '-' || kflag[0] == '/') && strcmp(&kflag[1], valid_flag) == 0;
}

int GetOpts(int argc, char** argv, kOpts* option, double* x, double* epsilon) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <a/b/c/d> <x> <epsilon>\n", argv[0]);
		return 1;
	}

	char *end, *end1;
	*x = MyStrtod(argv[2], &end);
	*epsilon = MyStrtod(argv[3], &end1);
	if (*end != '\0' || *end != '\0') {
		return 2;
	}

	char* flags[4] = {"a", "b", "c", "d"};

	for (int i = 0; i < 4; i++) {
		if (CheckFlag(argv[1], flags[i])) {
			*option = i;
			return 0;
		}
	}

	return 3;
}

int main(int argc, char* argv[]) {
    kOpts opt = 0;
	int number = 0;

	double x;
	double epsilon;

	void (*functions[4])(double, double) = {SumA, SumB, SumC, SumD};
	char* flags[4] = {"a", "b", "c", "d"};

	int res = GetOpts(argc, argv, &opt, &x, &epsilon);
	switch (res) {
		case 0:
			break;
		case 1:
			printf("Incorrect number of arguments.\n");
			return 1;
		case 2:
			printf("Error: %s or %s aren't a double number.\n", argv[2], argv[3]);
			return 1;
		case 3:
			printf("Unknown flag: %s\n", argv[1]);
			return 1;
		default:
			printf("Unknown error.\n");
			return 1;
	}

	functions[opt](x, epsilon);

	return 0;
}
