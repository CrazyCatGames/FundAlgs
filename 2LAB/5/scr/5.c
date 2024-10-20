#include "../include/5.h"

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kOpt ToRoman(int number, char **roman_value) {
	const int numbers[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
	const char letters[13][2] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
	int roman_size = 0;
	int roman_capacity = 2;
	(*roman_value) = (char *)malloc(sizeof(char) * roman_capacity);
	if (*roman_value == NULL) {
		return OPT_ERROR_ALLOC;
	}

	if (number < 0) {
		(*roman_value)[0] = '-';
		roman_size++;
		number = abs(number);
	}

	while (number) {
		int index = 13;
		while (numbers[--index] > number);

		for (int i = 0; i < 2; i++) {
			if (letters[index][i] == 'I' || letters[index][i] == 'V' || letters[index][i] == 'X' ||
			    letters[index][i] == 'L' || letters[index][i] == 'C' || letters[index][i] == 'D' ||
			    letters[index][i] == 'M') {
				(*roman_value)[roman_size] = letters[index][i];
				roman_size++;
				if (roman_size == roman_capacity - 1) {
					roman_capacity *= 2;
					char *new_memory = (char *)realloc(*roman_value, sizeof(char) * roman_capacity);
					if (new_memory == NULL) {
						return OPT_ERROR_ALLOC;
					}
					*roman_value = new_memory;
				}
			}
		}
		number -= numbers[index];
	}

	(*roman_value)[roman_size] = '\0';
	return OPT_SUCCESS;
}

void Fibonacci(unsigned int result[2], unsigned int number) {
	unsigned int count = 0;
	unsigned int tmp1 = 0, tmp2 = 1;
	unsigned int next = tmp1 + tmp2;
	while (next <= number) {
		tmp1 = tmp2;
		tmp2 = next;
		next = tmp1 + tmp2;
		count++;
	}

	result[0] = count;
	result[1] = tmp2;
}

void Zeckendorf(int *result_size, unsigned int number, unsigned int result[number][2]) {
	(*result_size) = 0;
	while (number) {
		Fibonacci(result[*result_size], number);
		(*result_size)++;
		number -= result[(*result_size) - 1][1];
	}
}

char *MemoryDump(void *src, int size) {
	char *res = (char *)malloc((9 * size) * sizeof(char));
	if (!res) {
		return NULL;
	}

	char *ptr = (char *)src;

	int idx = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 7; j >= 0; --j) {
			res[idx++] = (ptr[i] & (1 << j)) ? '1' : '0';
		}
		res[idx++] = ' ';
	}

	res[--idx] = '\0';
	return res;
}

kOpt FromDecimal(long long decimal_number, int base, int flag, char **result) {
	if (base < 2 || base > 36) {
		base = 10;
	}

	int index = 0;
	bool is_minus = false;
	(*result) = (char *)malloc((33) * sizeof(char));
	if (*result == NULL) {
		return OPT_ERROR_ALLOC;
	}

	int size = 0;
	if (decimal_number == 0) {
		(*result)[index] = '0';
		(*result)[index + 1] = '\0';
		return OPT_SUCCESS;
	}

	if (decimal_number < 0) {
		is_minus = true;
		(*result)[index++] = '-';
		size++;
	}

	decimal_number = abs((int)decimal_number);
	while (decimal_number) {
		long long remainder = decimal_number % base;
		if (remainder < 10) {
			(*result)[index++] = remainder + '0';
		} else {
			if (flag) {
				(*result)[index++] = remainder - 10 + 'A';
			} else {
				(*result)[index++] = remainder - 10 + 'a';
			}
		}

		size++;
		if (size > sizeof(*result) - 1) {
			char *new_result = (char *)realloc(*result, (size * 2) * sizeof(char));
			if (new_result == NULL) {
				return OPT_ERROR_ALLOC;
			}
			*result = new_result;
		}

		decimal_number /= base;
	}

	(*result)[size] = '\0';

	unsigned long long len = strlen(*result);
	for (int i = 0, j = 0; len - 1 - j > i; i++, j++) {
		if (is_minus) {
			i++;
			is_minus = false;
		}
		char tmp = (*result)[i];
		(*result)[i] = (*result)[len - 1 - j];
		(*result)[len - 1 - j] = tmp;
	}

	return OPT_SUCCESS;
}

kOpt ToDecimal(char *number_str, int base, long long *dec_number, int flag) {
	if (base < 2 || base > 36) {
		base = 10;
	}

	unsigned long long decimal_number = 0;
	unsigned long long power = strlen(number_str) - 1;
	bool start = true;
	bool minus = false;
	for (int i = 0; i < strlen(number_str); i++) {
		char digit = number_str[i];
		if (digit == '-' && start) {
			power--;
			start = false;
			minus = true;
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

		if (base <= digit_value) {
			return OPT_INVALID_PARAMETER;
		}

		decimal_number += digit_value * pow(base, power);
		power--;
		start = false;
	}

	if (decimal_number > INT_MAX) {
		return OPT_INVALID_PARAMETER;
	}

	*dec_number = minus ? -1 * decimal_number : decimal_number;
	return OPT_SUCCESS;
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

int overfprintf(FILE *stream, char *format, ...) {
	if (!(stream && format)) return -1;

	va_list args;
	va_start(args, format);

	unsigned long long len_format = strlen(format);
	int count = 0;

	for (int i = 0; i < len_format; ++i) {
		if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'R' && format[i + 2] == 'o') {
			int x = va_arg(args, int);
			char *roman_value = NULL;
			kOpt st_roman = ToRoman(x, &roman_value);
			if (st_roman == OPT_ERROR_ALLOC) {
				printf("Error malloc memory\n");
				free(roman_value);
				return -2;
			}

			count += fprintf(stream, "%s", roman_value);
			i += 2;
			free(roman_value);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'Z' && format[i + 2] == 'r') {
			unsigned int number = va_arg(args, unsigned int);
			int res_size;
			unsigned int res[number][2];
			Zeckendorf(&res_size, number, res);
			int count1 = 1;
			int j = res_size - 1;
			while (j >= 0) {
				if (count1 == res[j][0]) {
					count += fprintf(stream, "1");
					j--;
				} else {
					count += fprintf(stream, "0");
				}

				count1++;
			}

			count += fprintf(stream, "1");
			i += 2;
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'v') {
			long long number_to_convert = va_arg(args, long long);
			int base = va_arg(args, int);
			char *result = NULL;
			kOpt st_convert = FromDecimal(number_to_convert, base, 0, &result);
			if (st_convert == OPT_ERROR_ALLOC) {
				free(result);
				printf("Error malloc memory.\n");
				return -2;
			}

			count += fprintf(stream, "%s", result);
			free(result);
			i += 2;
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'V') {
			long long number_to_convert = va_arg(args, long long);
			int base = va_arg(args, int);
			char *result = NULL;
			kOpt st_convert = FromDecimal(number_to_convert, base, 1, &result);
			if (st_convert == OPT_ERROR_ALLOC) {
				free(result);
				printf("Error malloc memory\n");
				return -2;
			}

			count += fprintf(stream, "%s", result);
			free(result);
			i += 2;
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 't' && format[i + 2] == 'o') {
			char *num_to_convert = va_arg(args, char *);
			unsigned long long size = strlen(num_to_convert);
			int base = va_arg(args, int);
			long long result = 0;

			if (!is_lower(num_to_convert, size)) {
				count += fprintf(stream, "Letters are in upper case");
				i += 2;
				continue;
			}

			kOpt st_convert = ToDecimal(num_to_convert, base, &result, 0);
			if (st_convert == OPT_INVALID_PARAMETER) {
				count += fprintf(stream, "Invalid parameter");
				i += 2;
				continue;
			}

			count += fprintf(stream, "%lld", result);
			i += 2;
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'T' && format[i + 2] == 'O') {
			char *num_to_convert = va_arg(args, char *);
			unsigned long long size = strlen(num_to_convert);
			int base = va_arg(args, int);
			long long result = 0;

			if (!is_upper(num_to_convert, size)) {
				count += fprintf(stream, "Letters are in upper case ");
				i += 2;
				continue;
			}

			kOpt st_convert = ToDecimal(num_to_convert, base, &result, 1);
			if (st_convert == OPT_INVALID_PARAMETER) {
				count += fprintf(stream, "Invalid parameter ");
				i += 2;
				continue;
			}

			count += fprintf(stream, "%lld", result);
			i += 2;
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'i') {
			int x = va_arg(args, int);
			char *res;
			res = MemoryDump(&x, sizeof(int));
			if (res) {
				count += fprintf(stream, "%s", res);
			} else {
				printf("Error malloc memory.\n");
				return -2;
			}

			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'u') {
			unsigned int x = va_arg(args, unsigned int);
			char *res;
			res = MemoryDump(&x, sizeof(unsigned int));
			if (res) {
				count += fprintf(stream, "%s", res);
			} else {
				printf("Error malloc memory.\n");
				return -2;
			}

			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'd') {
			double x = va_arg(args, double);
			char *res;
			res = MemoryDump(&x, sizeof(double));
			if (res) {
				count += fprintf(stream, "%s", res);
			} else {
				printf("Error malloc memory.\n");
				return -2;
			}

			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'f') {
			float x = (float)va_arg(args, double);
			char *res;
			res = MemoryDump(&x, sizeof(float));
			if (res) {
				count += fprintf(stream, "%s", res);
			} else {
				printf("Error malloc memory.\n");
				return -2;
			}
			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 1) {
			char cur_format[7];
			cur_format[0] = '%';
			int j;
			for (j = i + 1; j < i + 6 && format[j] != '%' && j < len_format; ++j) {
				cur_format[j - i] = format[j];
			}
			cur_format[j - i] = '\0';
			i = j - 1;
			count += vfprintf(stream, cur_format, args);
			void* x = va_arg(args, void*);
		} else {
			count += fprintf(stream, "%c", format[i]);
		}
	}
	va_end(args);
	return count;
}

int oversprintf(char *buf, char *format, ...) {
	if (!(buf && format)) return -1;

	va_list args;
	va_start(args, format);

	unsigned long long len_format = strlen(format), count = 0;

	for (int i = 0; i < len_format; ++i) {
		if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'R' && format[i + 2] == 'o') {
			char *roman_value = NULL;
			kOpt st_roman = ToRoman(va_arg(args, int), &roman_value);
			if (st_roman == OPT_ERROR_ALLOC) {
				printf("Error malloc memory.\n");
				free(roman_value);
				return -2;
			}

			count += sprintf(buf + count, "%s", roman_value);
			i += 2;
			free(roman_value);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'Z' && format[i + 2] == 'r') {
			unsigned int number = va_arg(args, unsigned int);
			int res_size;
			unsigned int res[number][2];
			Zeckendorf(&res_size, number, res);
			int count1 = 1;
			int j = res_size - 1;
			while (j >= 0) {
				if (count1 == res[j][0]) {
					count += sprintf(buf + count, "1");
					j--;
				} else {
					count += sprintf(buf + count, "0");
				}

				count1++;
			}

			i += 2;
			count += sprintf(buf + count, "1");
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'v') {
			int x = va_arg(args, int);
			int base = va_arg(args, int);
			char *res = NULL;
			kOpt st_convert = FromDecimal(x, base, 0, &res);
			if (st_convert == OPT_ERROR_ALLOC) {
				free(res);
				printf("Error malloc memory.\n");
				return -2;
			}

			unsigned long long len = strlen(res);
			for (int j = 0; j < len; ++j) res[j] = tolower(res[j]);
			count += sprintf(buf + count, "%s", res);
			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'V') {
			int x = va_arg(args, int);
			int base = va_arg(args, int);
			char *res = NULL;
			kOpt st_convert = FromDecimal(x, base, 1, &res);
			if (st_convert == OPT_ERROR_ALLOC) {
				free(res);
				printf("Error malloc memory.\n");
				return -2;
			}

			unsigned long long len = strlen(res);
			for (int j = 0; j < len; ++j) {
				res[j] = tolower(res[j]);
			}

			count += sprintf(buf + count, "%s", res);
			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 't' && format[i + 2] == 'o') {
			char *num_to_convert = va_arg(args, char *);
			unsigned long long size = strlen(num_to_convert);
			int base = va_arg(args, int);
			long long result = 0;

			if (!is_lower(num_to_convert, size)) {
				count += sprintf(buf + count, "Letters are in upper case");
				i += 2;
				continue;
			}

			kOpt st_convert = ToDecimal(num_to_convert, base, &result, 0);
			if (st_convert == OPT_INVALID_PARAMETER) {
				count += sprintf(buf + count, "Invalid parameter");
				i += 2;
				continue;
			}

			i += 2;
			count += sprintf(buf + count, "%lld", result);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'T' && format[i + 2] == 'O') {
			char *num_to_convert = va_arg(args, char *);
			unsigned long long size = strlen(num_to_convert);
			int base = va_arg(args, int);
			long long result = 0;

			if (!is_upper(num_to_convert, size)) {
				count += sprintf(buf + count, "Letters are in upper case");
				i += 2;
				continue;
			}

			kOpt st_convert = ToDecimal(num_to_convert, base, &result, 1);
			if (st_convert == OPT_INVALID_PARAMETER) {
				count += sprintf(buf + count, "Invalid parameter");
				i += 2;
				continue;
			}

			i += 2;
			count += sprintf(buf + count, "%lld", result);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'i') {
			int ix = va_arg(args, int);
			char *res;
			res = MemoryDump(&ix, sizeof(int));
			if (res) {
				count += sprintf(buf + count, "%s", res);
			} else {
				printf("Error malloc memeory.\n");
				return -2;
			}
			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'u') {
			unsigned int ix = va_arg(args, unsigned int);
			char *res;
			res = MemoryDump(&ix, sizeof(unsigned int));
			if (res) {
				count += sprintf(buf + count, "%s", res);
			} else {
				printf("Error malloc memeory.\n");
				return -2;
			}

			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'd') {
			double dx = va_arg(args, double);
			char *res;
			res = MemoryDump(&dx, sizeof(double));
			if (res) {
				count += sprintf(buf + count, "%s", res);
			} else {
				printf("Error malloc memeory.\n");
				return -2;
			}

			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'f') {
			int fx = va_arg(args, double);
			char *res;
			res = MemoryDump(&fx, sizeof(float));
			if (res) {
				count += sprintf(buf + count, "%s", res);
			} else {
				printf("Error malloc memeory.\n");
				return -2;
			}

			i += 2;
			free(res);
		} else if (format[i] == '%' && i < len_format - 1) {
			char cur_format[7];
			cur_format[0] = '%';
			int j;
			for (j = i + 1; j < i + 6 && format[j] != '%' && j < len_format; ++j) {
				cur_format[j - i] = format[j];
			}

			cur_format[j - i] = '\0';
			i = j - 1;
			count += vsprintf(buf + count, cur_format, args);
		} else {
			buf[count++] = format[i];
		}
	}
	buf[count] = '\0';
	va_end(args);
	return count;
}
