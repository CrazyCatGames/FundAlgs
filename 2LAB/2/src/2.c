#include "../include/2.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

kOpts GeomMean(double* res, int count, ...) {
	if (count < 1) {
		return OPT_ERROR_INVALID;
	}

	va_list ptr;
	*res = 1;
	va_start(ptr, count);
	for (int i = 0; i < count; i++) {
		double value = va_arg(ptr, double);
		*res *= value;
	}

	*res = pow(*res, 1.0 / count);
	va_end(ptr);

	if (isinf(*res)) {
		return OPT_ERROR_OVERFLOW;
	}
	if (isnan(*res)) {
		return OPT_ERROR_NAN;
	}

	return OPT_SUCCESS;
}

kOpts FastPow(double* res, double value, int power) {
	if (power < 0) {
		return FastPow(res, 1 / value, -power);
	} else if (power == 0) {
		*res = 1.0;
		return OPT_SUCCESS;
	} else if (power % 2 == 0) {
		double temp;
		kOpts opt_status = FastPow(&temp, value * value, power / 2);
		if (opt_status == OPT_SUCCESS) {
			*res = temp;
			if (isinf(*res)) {
				return OPT_ERROR_OVERFLOW;
			}else if (isnan(*res)) {
				return OPT_ERROR_NAN;
			}
		}
		return opt_status;
	} else {
		double temp;
		kOpts opt_status = FastPow(&temp, value * value, (power - 1) / 2);
		if (opt_status == OPT_SUCCESS) {
			*res = temp * value;
			if (isinf(*res)) {
				return OPT_ERROR_OVERFLOW;
			}else if (isnan(*res)) {
				return OPT_ERROR_NAN;
			}
		}
		return opt_status;
	}

	return OPT_FAIL;
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
		str++;
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

char *read_input() {
	size_t length = 0, input_size = 1;
	char *input_str = (char *)malloc(input_size * sizeof(char));
	if (!input_str) {
		return NULL;
	}

	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF) {
		if (length + 1 >= input_size) {
			input_size *= 2;
			char *temp = realloc(input_str, input_size);
			if (!temp) {
				free(input_str);
				return NULL;
			}
			input_str = temp;
		}
		input_str[length++] = (char)ch;
	}
	input_str[length] = '\0';

	return input_str;
}
