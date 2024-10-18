#include "../include/10.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IsGreater(const char *num1, const char *num2, int base) {
	int len1 = strlen(num1);
	int len2 = strlen(num2);

	if (len1 != len2) {
		return len1 > len2;
	}

	return strcmp(num1, num2) > 0;
}

long long ConvertToDecimal(const char *num, int from_base, int *error) {
	long long result = 0;
	long long multiplier = 1;

	for (int i = strlen(num) - 1; i >= 0; i--) {
		int digit = isdigit(num[i]) ? num[i] - '0' : toupper(num[i]) - 'A' + 10;

		if (digit < 0 || digit >= from_base) {
			*error = 1;
			return 0;
		}

		if (result > (LLONG_MAX - digit) / from_base) {
			*error = 2;
			return 0;
		}

		result += digit * multiplier;
		multiplier *= from_base;
	}
	return result;
}

char *ConvertBase(const char *num, int from_base, int to_base, int *error) {
	long long decimal_value = ConvertToDecimal(num, from_base, error);

	if (*error) {
		return NULL;
	}

	char *result = malloc(65);
	if (!result) {
		return NULL;
	}

	int index = 0;
	if (decimal_value == 0) {
		result[index++] = '0';
	} else {
		while (decimal_value > 0) {
			int digit = decimal_value % to_base;
			result[index++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
			decimal_value /= to_base;
		}
	}
	result[index] = '\0';

	for (int i = 0; i < index / 2; i++) {
		char temp = result[i];
		result[i] = result[index - i - 1];
		result[index - i - 1] = temp;
	}

	return result;
}

int IsValidNumber(const char *num, int base) {
	for (int i = 0; num[i] != '\0'; i++) {
		char c = num[i];
		int value;

		if (c >= '0' && c <= '9') {
			value = c - '0';
		} else if (c >= 'A' && c <= 'Z') {
			value = c - 'A' + 10;
		} else {
			return 0;
		}

		if (value >= base) {
			return 0;
		}
	}
	return 1;
}