#include "../include/1.h"
#include <stdio.h>
#include <stdlib.h>

void PrintResult(const char *result, int size) {
	int i;
	printf("Result: ");
	for (i = Add(size, Add(~1, 1)); i >= 0; i = Add(i, Add(~1, 1))) {
		putchar(result[i]);
	}
	putchar('\n');
}

int Add(int a, int b) {
	while (b != 0) {
		int carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}

	return a;
}

kOpt Convert(char **ans, int *size, int number, int power, size_t *size_res) {
	int mask, digit;
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
		mask = Add(1 << power, Add(~1, 1));
		digit = number & mask;
		number >>= power;
		if (*size >= *size_res){
			*size_res *= 2;
			char *tmp = (char*)realloc(*ans, sizeof(char) * *size_res);
			if (!tmp){
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