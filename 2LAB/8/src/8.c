#include "../include/8.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

unsigned int MyStrlen(const char *str) {
	size_t length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

kOpt CheckDigit(int *digit, unsigned int len, int i, const char *num, int base) {
	if (i < len) {
		char ch = num[len - 1 - i];
		if (isdigit(ch)) {
			*digit = ch - '0';
		} else if (isalpha(ch)) {
			*digit = tolower(ch) - 'a' + 10;
		}else{
			return OPT_ERROR_NUMBER;
		}
		if (*digit >= base) {
			return OPT_ERROR_NUMBER;
		}
	}else {
		*digit = 0;
	}
	return OPT_SUCCESS;
}

kOpt addInColumn(const char *num1, const char *num2, int base, char **result, size_t *result_size) {
	unsigned int len1 = MyStrlen(num1);
	unsigned int len2 = MyStrlen(num2);
	int carry = 0, i = 0;

	size_t temp_size = *result_size;
	char *temp = (char *)malloc(temp_size * sizeof(char));
	if (temp == NULL) {
		return OPT_ERROR_MEMORY;
	}

	unsigned int max_len = len1 > len2 ? len1 : len2;

	for (i = 0; i < max_len || carry; i++) {
		if (i >= temp_size - 1) {
			size_t new_temp_size = temp_size * 2;
			char *new_temp = (char *)realloc(temp, new_temp_size * sizeof(char));
			if (new_temp == NULL) {
				free(temp);
				return OPT_ERROR_MEMORY;
			}
			temp = new_temp;
			temp_size = new_temp_size;
		}

		int digit1 = 0;
		if (CheckDigit(&digit1, len1, i, num1, base) == OPT_ERROR_NUMBER) {
			free(temp);
			return OPT_ERROR_NUMBER;
		}

		int digit2 = 0;
		if (CheckDigit(&digit2, len2, i, num2, base) == OPT_ERROR_NUMBER) {
			free(temp);
			return OPT_ERROR_NUMBER;
		}

		int sum = digit1 + digit2 + carry;
		carry = sum / base;
		sum %= base;

		temp[i] = sum < 10 ? '0' + sum : 'a' + (sum - 10);
	}
	temp[i] = '\0';

	if (i >= *result_size) {
		size_t new_result_size = i + 1;
		char *new_result = (char *)realloc(*result, new_result_size * sizeof(char));
		if (new_result == NULL) {
			free(temp);
			return OPT_ERROR_MEMORY;
		}
		*result = new_result;
		*result_size = new_result_size;
	}

	for (int j = 0; j < i; j++) {
		(*result)[j] = temp[i - j - 1];
	}
	(*result)[i] = '\0';

	free(temp);
	return OPT_SUCCESS;
}

void removeLeadingZeros(char *str) {
	unsigned int len = MyStrlen(str);
	int i = 0;

	while (i < len && str[i] == '0') {
		i++;
	}
	if (i == len) {
		str[1] = '\0';
	} else if (i > 0) {
		memmove(str, str + i, len - i + 1);
	}
}

kOpt sumNumbersInBase(int base, char **result, size_t *result_size, int count, ...) {
	strcpy(*result, "0");
	if ((2 > base) || (36 < base)){
		return OPT_ERROR_BASE;
	}
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; i++) {
		const char *num = va_arg(args, const char *);
		kOpt check;
		if ((check = addInColumn(*result, num, base, result, result_size)) == OPT_ERROR_MEMORY) {
			return OPT_ERROR_MEMORY;
		}else if (check == OPT_ERROR_NUMBER){
			return OPT_ERROR_NUMBER;
		}
	}

	va_end(args);

	removeLeadingZeros(*result);
	return OPT_SUCCESS;
}