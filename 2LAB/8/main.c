#include <stdio.h>
#include <stdlib.h>

#include "include/8.h"

int main(void) {
	size_t result_size = 50;
	char *result = (char *)malloc(result_size * sizeof(char));
	if (result == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

	kOpt res = sumNumbersInBase(16, &result, &result_size, 3, "00000000000000000aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "00000000bbbbbbb", "fffffffffffff0ff");

	if (res == OPT_SUCCESS) {
		printf("Result: %s\n", result);
	} else if (res == OPT_ERROR_NUMBER) {
		fprintf(stderr, "Incorrect values.\n");
	} else if (res == OPT_ERROR_BASE) {
		fprintf(stderr, "Incorrect base.\n");
	} else {
		fprintf(stderr, "Error memory allocation.\n");
	}

	free(result);
	return 0;
}
