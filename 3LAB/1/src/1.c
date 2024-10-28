#include "../include/1.h"
#include <stdio.h>
#include <stdlib.h>

void PrintResult(const char *result, int size) {
	int i;
	char minus_one = Add(~1, 1);
	printf("Result: ");
	for (i = Add(size, minus_one); i >= 0; i = Add(i, minus_one)) {
		putchar(result[i]);
	}
	putchar('\n');
}

int Add(int a, int b) {
	int keep = (a & b) << 1;
	int res = a ^ b;
	if (keep == 0) return res;

	return Add(keep, res);
}

kOpt Convert(char **ans, int *size, int number, int power, size_t *size_res) {
	int mask, digit;
	int minus_one = Add(~1, 1);
	char base[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV", flag = 0;
	*size = 0;
	if (!ans || power < 1 || power > 5) {
		return OPT_ERROR;
	}

	if (number < 0) {
		number = Add(~number, 1);
		flag = '1';
	}

	do {
		mask = Add(1 << power, minus_one);
		digit = number & mask;
		number >>= power;
		if (*size >= *size_res){
			*size_res = Add(*size_res, *size_res);
			char *tmp = (char *)realloc(*ans, *size_res);
			if (!tmp) {
				return OPT_MEMORY;
			}
			*ans = tmp;
		}

		(*ans)[*size] = base[digit];
		*size = Add(*size, 1);
	} while (number);

	if (flag) {
		(*ans)[*size] = '-';
		*size = Add(*size, 1);
	}

	return OPT_SUCCESS;
}