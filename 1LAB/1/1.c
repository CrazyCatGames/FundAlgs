#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum kOpts { OPT_H, OPT_P, OPT_S, OPT_E, OPT_A, OPT_F, OPT_SUCCESS, OPT_ERROR_LIMITS, OPT_ERROR_MEMORY } kOpts;

// Find prime numbers multiples of the first 100 numbers.
kOpts FlagH(int x, char* output) {
	if (x > 100 || x < 1) {
		sprintf(output, "%d is greater than 100 or lower than 1.\n", x);
		return OPT_ERROR_LIMITS;
	} else {
		int found = 0;
		char buffer[256] = {0};
		sprintf(buffer, "Natural numbers, multiples of %d within 100: ", x);
		for (int i = 1; i <= 100; i++) {
			if (i % x == 0) {
				found = x;
				break;
			}
		}
		if (found == 0) {
			strcat(buffer, "There are no multiples.\n");
		} else {
			for (int i = 1; i <= 100 / found; i++) {
				char temp[10];
				sprintf(temp, "%d ", x * i);
				strcat(buffer, temp);
			}
		}
		strcpy(output, buffer);
		return OPT_SUCCESS;
	}
}

// X to 16cc
kOpts FlagS(int x, char* output) {
	if (x < 0) {
		sprintf(output, "Please enter a non-negative integer.\n");
		return OPT_ERROR_LIMITS;
	}

	char buffer[128] = {0};
	sprintf(buffer, "The digits of the number %d in the 16-bit system: ", x);

	if (x == 0) {
		strcat(buffer, "0");
		strcpy(output, buffer);
		return OPT_SUCCESS;
	}

	int hex_digits[64], count = 0;
	while (x > 0) {
		hex_digits[count++] = x % 10;
		x /= 10;
	}

	for (int i = count - 1; i >= 0; i--) {
		char temp[10];
		sprintf(temp, "%X ", hex_digits[i]);
		strcat(buffer, temp);
	}

	strcpy(output, buffer);
	return OPT_SUCCESS;
}

// Table of degrees.
kOpts FlagE(int x, char* output) {
	if (x < 1 || x > 10) {
		sprintf(output, "Please enter a valid exponent between 1 and 10.\n");
		return OPT_ERROR_LIMITS;
	}

	char buffer[256];
	output[0] = '\0';

	for (int base = 1; base <= 10; base++) {
		for (int power = 1; power <= x; power++) {
			unsigned long long result = 1;
			for (int p = 1; p <= power; p++) {
				result *= base;
			}

			sprintf(buffer, "%llu ", result);
			strcat(output, buffer);
		}
	}

	return OPT_SUCCESS;
}

// x is prime number.
kOpts FlagP(int x, char* output) {
	if (x <= 1) {
		sprintf(output, "%d is neither a prime number nor a composite number.\n", x);
		return OPT_ERROR_LIMITS;
	}

	int is_prime = 1;
	for (int i = 2; i <= sqrt(x); i++) {
		if (x % i == 0) {
			is_prime = 0;
			break;
		}
	}

	if (is_prime) {
		sprintf(output, "%d is a prime number", x);
	} else {
		sprintf(output, "%d is a composite number", x);
	}
	return OPT_SUCCESS;
}

// Summ of 1 to x.
kOpts FlagA(int x, char* output) {
	if (x < 0) {
		sprintf(output, "%d is a negative number.\n", x);
		return OPT_ERROR_LIMITS;
	}

	int sum = (x * (x + 1)) / 2;
	sprintf(output, "Sum from 1 to %d: %d", x, sum);
	return OPT_SUCCESS;
}

void MultiplyString(char num[], int factor) {
	int term = 0;

	for (int i = strlen(num) - 1; i >= 0; i--) {
		int digit = num[i] - '0';
		int product = digit * factor + term;
		num[i] = (product % 10) + '0';
		term = product / 10;
	}

	while (term) {
		for (int i = strlen(num); i >= 0; i--) {
			num[i + 1] = num[i];
		}
		num[0] = (term % 10) + '0';
		term /= 10;
	}
}

// Factorial of x.
kOpts FlagF(int x, char* output) {
	if (x < 0 || x > 450) {
		sprintf(output, "%d is a negative number or %d is too big for factorial.\n", x, x);
		return OPT_ERROR_LIMITS;
	}

	char* fact = (char*)malloc(1000 * sizeof(char));
	if (!fact) {
		sprintf(output, "Memory allocation failed.\n");
		return OPT_ERROR_MEMORY;
	}

	strcpy(fact, "1");

	for (int i = 2; i <= x; i++) {
		MultiplyString(fact, i);
	}

	sprintf(output, "Factorial of %d: %s", x, fact);
	free(fact);
	return OPT_SUCCESS;
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

int CheckFlag(const char* kflag, char* valid_flag) {
	return (kflag[0] == '-' || kflag[0] == '/') && strcmp(&kflag[1], valid_flag) == 0;
}

int GetOpts(int argc, char** argv, kOpts* option, int* number) {
	if (argc != 3) {
		return 1;
	}

	char* end;
	*number = MyStrtoi(argv[2], &end);
	if (*end != '\0') {
		return 2;
	}

	char* flags[6] = {"h", "p", "s", "e", "a", "f"};

	for (int i = 0; i < 6; i++) {
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
	char output[1024]; 
	kOpts (*func[6])(int, char*) = {FlagH, FlagP, FlagS, FlagE, FlagA, FlagF};

	int result = GetOpts(argc, argv, &opt, &number);
	if (result != 0) {
		switch (result) {
			case 1:
				printf("Incorrect number of arguments.\n");
				break;
			case 2:
				printf("Error: %s isn't a natural number.\n", argv[2]);
				break;
			case 3:
				printf("Unknown flag: %s\n", argv[1]);
				break;
			default:
				printf("Unknown error.\n");
		}
		return 1;
	}

	kOpts res = func[opt](number, output);

	if (res == OPT_SUCCESS && opt == OPT_E) {
		char* token = strtok(output, " ");

		for (int base = 1; base <= 10; base++) {
			printf("Base %d: ", base);
			for (int power = 1; power <= number; power++) {
				if (token != NULL) {
					printf("%3d^%d=%s ", base, power, token);
					token = strtok(NULL, " ");
				}
			}
			printf("\n");
		}
	} else if (res == OPT_SUCCESS) {
		printf("%s\n", output);
	} else {
		printf("%s", output);
		printf("Error occurred.\n");
	}

	return 0;
}
