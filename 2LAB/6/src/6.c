#include "../include/6.h"
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

optRealloc MyRealloc(void **var, int size) {
	void *new_ptr = realloc(*var, size);
	if (new_ptr != NULL) {
		*var = new_ptr;
		return OPT_REALLOC_SUCCESS;
	} else {
		return OPT_REALLOC_FAIL;
	}
}

bool is_digit_str(const char *str, int size) {
	for (int i = 0; i < size; i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool is_lower(const char *str, int size) {
	for (int i = 0; i < size; i++) {
		if ((str[i] >= 'A') && (str[i] <= 'Z')) {
			return false;
		}
	}
	return true;
}

bool is_upper(const char *str, int size) {
	for (int i = 0; i < size; i++) {
		if ((str[i] >= 'a') && (str[i] <= 'z')) {
			return false;
		}
	}
	return true;
}

kOpt FromRoman(const char *number_str, int *num) {
	int size = strlen(number_str);
	if (!size) {
		return OPT_INVALID_PARAMETER;
	}

	*num = 0;
	int sign;
	if (number_str[0] == '-') {
		sign = -1;
	} else {
		sign = 1;
	}

	for (int i = size - 1; i >= 0; i--) {
		char symbol = number_str[i];
		switch (symbol) {
			case 'I':
				if (number_str[i + 1] == 'X' || number_str[i + 1] == 'V') {
					(*num)--;
				} else {
					(*num)++;
				}
				break;
			case 'V':
				(*num) += 5;
				break;
			case 'X':
				if (number_str[i + 1] == 'L' || number_str[i + 1] == 'C') {
					(*num) -= 10;
				} else {
					(*num) += 10;
				}
				break;
			case 'L':
				(*num) += 50;
				break;
			case 'C':
				if (number_str[i + 1] == 'D' || number_str[i + 1] == 'M') {
					(*num) -= 100;
				} else {
					(*num) += 100;
				}
				break;
			case 'M':
				(*num) += 1000;
				break;
			default:
				break;
		}
	}

	*num *= sign;
	return OPT_SUCCESS;
}

kOpt FromZeckendorf(const char *number_z, unsigned int *number) {
	int size = strlen(number_z);
	if (!size) {
		return OPT_INVALID_PARAMETER;
	}

	unsigned int num1 = 0;
	unsigned int num2 = 1;
	unsigned int cur = 1;
	*number = 0;
	for (int i = 0; i < size - 1; i++) {
		char symb = number_z[i];
		if (symb == '1') {
			(*number) += cur;
		}
		num1 = num2;
		num2 = cur;
		cur = num1 + num2;
	}

	return OPT_SUCCESS;
}

kOpt ToDecimal(char *number_str, int base, int *dec_number, int flag) {
	if (base < 2 || base > 36) {
		base = 10;
	}

	long long decimal_number = 0;
	int power = strlen(number_str) - 1;
	bool start = true;
	bool is_minus = false;
	for (int i = 0; i < strlen(number_str); i++) {
		char digit = number_str[i];
		if (digit == '-' && start) {
			power--;
			start = false;
			is_minus = true;
			continue;
		}

		int digit_value;
		if (isdigit(digit)) {
			digit_value = digit - '0';
		} else if (isalpha(digit)) {
			if (flag) {
				digit_value = digit - 'A' + 10;
			} else {
				digit_value = digit - 'a' + 10;
			}
		} else {
			return OPT_INVALID_PARAMETER;
		}

		decimal_number += digit_value * pow(base, power);
		power--;
		start = false;
	}

	if (decimal_number > INT_MAX) {
		return OPT_INVALID_PARAMETER;
	}

	*dec_number = is_minus ? -1 * decimal_number : decimal_number;
	return OPT_SUCCESS;
}


int overfscanf(FILE *stream, const char *format, ...) {
	if (!stream) {
		return -1;
	}

	int size_format = strlen(format);
	if (!size_format) {
		printf("There are no format to scan.\n");
		return -1;
	}

	int argc = 0;
	for (int i = 0; i < size_format; i++) {
		if (format[i] == '%') {
			if (format[i + 1] != '%') {
				argc++;
			}
		}
	}

	va_list ptr;
	va_start(ptr, format);
	int index = 0;
	char *flag = NULL;
	int ret_value = 0;
	for (int i = 0; i < argc; i++) {
		int size_flag = 1;
		int capacity_flag = 2;
		while (format[index] != '%' && index < size_format) {
			index++;
		}

		flag = (char *) malloc(sizeof(char) * (capacity_flag + 2));
		if (!flag) {
			printf("Error malloc memory.\n");
			return -1;
		}

		flag[0] = '%';
		index++;
		while ((isdigit(format[index])) || (isalpha(format[index])) && (index < size_format)) {
			char symbol = format[index];
			flag[size_flag] = symbol;
			size_flag++;

			if (size_flag == capacity_flag - 1) {
				capacity_flag *= 2;
				optRealloc st_realloc = MyRealloc((void **) flag, capacity_flag);
				if (st_realloc == OPT_REALLOC_FAIL) {
					free(flag);
					printf("Can`t realloc memory!\n");
					return -1;
				}
			}
			index++;
		}

		flag[size_flag] = '\0';
		if (!strcmp(flag, "%Ro\0")) {
			int *arg_ptr = va_arg(ptr, int *);
			char tmp[STR_SIZE];
			ret_value += fscanf(stream, "%s", tmp);
			FromRoman(tmp, arg_ptr);
		} else if (!strcmp(flag, "%Zr\0")) {
			unsigned int *arg_ptr = va_arg(ptr, unsigned int *);
			char tmp[STR_SIZE];
			ret_value += fscanf(stream, "%s", tmp);
			FromZeckendorf(tmp, arg_ptr);
		} else if (!strcmp(flag, "%Cv\0")) {
			int *arg_ptr = va_arg(ptr, int *);
			argc++;
			int base = va_arg(ptr, int);
			char number_str[STR_SIZE];
			ret_value += fscanf(stream, "%s", number_str);
			int size = strlen(number_str);

			if (is_upper(number_str, size) && !is_digit_str(number_str, size)) {
				printf("Letters are in upper case!!!\n");
				(*arg_ptr) = 0;
			} else {
				ToDecimal(number_str, base, arg_ptr, 0);
			}
		} else if (!strcmp(flag, "%CV\0")) {
			int *arg_ptr = va_arg(ptr, int *);
			argc++;
			int base = va_arg(ptr, int);
			char number_str[STR_SIZE];
			ret_value += fscanf(stream, "%s", number_str);
			int size = strlen(number_str);

			if (is_lower(number_str, size) && !is_digit_str(number_str, size)) {
				printf("Letters are in lower case\n");
				(*arg_ptr) = 0;
			} else {
				ToDecimal(number_str, base, arg_ptr, 1);
			}
		} else {
			void *tmp_arg = va_arg(ptr, void *);
			ret_value += fscanf(stream, flag, tmp_arg);
		}
		free(flag);
		flag = NULL;
	}

	va_end(ptr);
	return ret_value;
}

int oversscanf(char *buf, const char *format, ...) {
	if (!buf) {
		return -1;
	}

	int size_format = strlen(format);
	if (!size_format) {
		printf("There are no format to scan.\n");
		return -1;
	}

	int argc = 0;
	for (int i = 0; i < size_format; i++) {
		if (format[i] == '%') {
			if (format[i + 1] != '%') {
				argc++;
			}
		}
	}

	va_list ptr;
	va_start(ptr, format);
	int index = 0;
	int buf_index = 0;
	char *flag = NULL;
	int ret_value = 0;

	for (int i = 0; i < argc; i++) {
		int size_flag = 1;
		int capacity_flag = 2;
		while (format[index] != '%' && index < size_format) {
			index++;
		}

		flag = (char *) malloc(sizeof(char) * (capacity_flag + 2));
		if (!flag) {
			printf("Error malloc memory.\n");
			return -1;
		}

		flag[0] = '%';
		index++;
		while ((isdigit(format[index])) || (isalpha(format[index])) && (index < size_format)) {
			char symbol = format[index];
			flag[size_flag] = symbol;
			size_flag++;

			if (size_flag == capacity_flag - 1) {
				capacity_flag *= 2;
				optRealloc st_realloc = MyRealloc((void **) flag, capacity_flag);
				if (st_realloc == OPT_REALLOC_FAIL) {
					free(flag);
					printf("Can`t realloc memory!\n");
					return -1;
				}
			}
			index++;
		}

		flag[size_flag] = '\0';

		if (!strcmp(flag, "%Ro\0")) {
			int *arg_ptr = va_arg(ptr, int *);
			char tmp[STR_SIZE];
			ret_value += sscanf(buf_index + buf, "%s", tmp);
			buf_index += strlen(tmp) + 1;
			FromRoman(tmp, arg_ptr);
		} else if (!strcmp(flag, "%Zr\0")) {
			unsigned int *arg_ptr = va_arg(ptr, unsigned int *);
			char tmp[STR_SIZE];
			ret_value += sscanf(buf_index + buf, "%s", tmp);
			buf_index += strlen(tmp) + 1;
			FromZeckendorf(tmp, arg_ptr);
		} else if (!strcmp(flag, "%Cv\0")) {
			int *arg_ptr = va_arg(ptr, int *);
			argc++;
			int base = va_arg(ptr, int);
			char number_str[STR_SIZE];
			ret_value += sscanf(buf_index + buf, "%s", number_str);
			int size = strlen(number_str);
			buf_index += size + 1;

			if (is_upper(number_str, size) && !is_digit_str(number_str, size)) {
				printf("Letters are in upper case\n");
				(*arg_ptr) = 0;
			} else {
				ToDecimal(number_str, base, arg_ptr, 0);
			}

			argc--;
		} else if (!strcmp(flag, "%CV\0")) {
			int *arg_ptr = va_arg(ptr, int *);
			argc++;
			int base = va_arg(ptr, int);
			char number_str[STR_SIZE];
			ret_value += sscanf(buf_index + buf, "%s", number_str);
			int size = strlen(number_str);
			buf_index += size + 1;

			if (is_lower(number_str, size) && !is_digit_str(number_str, size)) {
				printf("Letters are in lower case\n");
				(*arg_ptr) = 0;
			} else {
				ToDecimal(number_str, base, arg_ptr, 1);
			}

			argc--;
		} else {
			void *tmp_arg = va_arg(ptr, void *);
			ret_value += sscanf(buf_index + buf, flag, tmp_arg);
			buf_index += strlen(tmp_arg) + 1;
		}

		free(flag);
		flag = NULL;
	}
	va_end(ptr);
	return ret_value;
}